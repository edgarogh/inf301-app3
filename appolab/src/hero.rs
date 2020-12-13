use appolab::AppoLabConnection;
use regex::Regex;
use std::collections::{HashSet, VecDeque};
use std::str::FromStr;

/// Représente une réponse du serveur, pour l'exo "hero"
#[derive(Debug, Eq, PartialEq)]
enum Response {
    /// Gagné
    Win,

    /// On est mort
    Death,

    /// Le serveur ne nous donne pas de choix, juste un numéro de page
    NoChoice(String),

    /// Le serveur nous laisse choisir entre deux pages
    Choice(String, String),
}

// Compilation lazy des Regex
lazy_static::lazy_static! {
    // Fin du type "[...] le choix entre la page 24 et la page 10."
    static ref RESPONE_REGEX: Regex = Regex::new(r#"([a-zA-Z0-9]+) et la page ([a-zA-Z0-9]+).$"#).unwrap();
    // Fin du type "[...] continue en page ngzRzMEs0"
    static ref RESPONE_REGEX_1: Regex = Regex::new(r#"continue en page ([a-zA-Z0-9]+)$"#).unwrap();
}

// Implémenter le trait `FromStr` sur ma structure permet d'en obtenir une instance avec la methode
// `parse()` des chaînes de caractère.
impl FromStr for Response {
    type Err = ();

    fn from_str(s: &str) -> Result<Self, Self::Err> {
        let s = s.trim();

        if s.contains("gagné") && !s.contains("Ha bah non") {
            return Ok(Response::Win);
        }

        Ok(match RESPONE_REGEX.captures(s) {
            Some(matches) => {
                let choice1 = matches.get(1).unwrap().as_str();
                let choice2 = matches.get(2).unwrap().as_str();
                Response::Choice(choice1.to_owned(), choice2.to_owned())
            }
            None => match RESPONE_REGEX_1.captures(s) {
                Some(matches) => Response::NoChoice(matches.get(1).unwrap().as_str().to_owned()),
                None => Response::Death,
            },
        })
    }
}

/// Petit test unitaire
#[test]
fn test_response_from_str() {
    let parsed: Response = "...maintenant le choix entre la page abc42 et la page 90b."
        .parse()
        .unwrap();
    assert_eq!(
        parsed,
        Response::Choice("abc42".to_owned(), "90b".to_owned())
    );
}

fn has_unique_elements<'a, T>(mut iter: T) -> bool
where
    T: Iterator<Item = &'a String>,
{
    let mut uniq = HashSet::new();
    iter.all(|x| uniq.insert(x))
}

pub fn hero_main(mut connection: AppoLabConnection) {
    connection.send_receive("load hero").unwrap();
    connection.send_receive("start").unwrap();

    // Liste (FIFO) des chemins à essayer
    let mut to_try = VecDeque::new();

    // Première connection, on sait qu'on nous donnera un choix, on initialise `to_try` pour
    // "lancer la machine"
    match connection
        .send_receive("AppelNonSurtaxe")
        .unwrap()
        .parse()
        .unwrap()
    {
        Response::Choice(c1, c2) => {
            let mut v1 = VecDeque::new();
            v1.push_back(c1);
            to_try.push_back(v1);
            let mut v2 = VecDeque::new();
            v2.push_back(c2);
            to_try.push_back(v2);
        }
        _ => unreachable!("first time is always a choice"),
    }

    // Du moment qu'il reste des chemins à essayer
    while let Some(mut path) = to_try.pop_front() {
        // S'il y a des boucles, on skip
        if !has_unique_elements(path.iter()) {
            continue;
        }

        // println!("=== {:?}", path);
        // println!("=== {:?}", &to_try);

        // Clone immutable du chemin courant
        let path_clone = path.clone();

        while let Some(choice) = path.pop_front() {
            match connection
                .send_receive(choice.to_string())
                .unwrap()
                .parse()
                .unwrap()
            {
                Response::Choice(choice1, choice2) => {
                    // Si le chemin à essayer est vide, on rajoute les sous-chemins à `to_try`
                    // et on envoie `start` pour redémarrer une aventure.
                    if path.is_empty() {
                        let mut p1 = path_clone.clone();
                        p1.push_back(choice1.clone());
                        to_try.push_back(p1);

                        let mut p2 = path_clone;
                        p2.push_back(choice2.clone());
                        to_try.push_back(p2);

                        connection.send_receive("start").unwrap();
                        break;
                    }
                }
                Response::NoChoice(page) => {
                    let mut clone = path_clone;
                    clone.push_back(page);
                    to_try.push_back(clone);
                    connection.send_receive("start").unwrap();
                    break;
                }
                Response::Death => {
                    connection.send_receive("start").unwrap();
                    break;
                }
                Response::Win => {
                    println!("Gagné");
                    connection.delegate_to_interactive();
                }
            }
        }
    }
}
