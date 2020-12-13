/// Nœud pouvant stocker des données génériques
pub struct GenericNode<T> {
    pub value: T,
    pub left: Option<Box<GenericNode<T>>>,
    pub right: Option<Box<GenericNode<T>>>,
}

/// Spécialisation du type ci-dessus
pub type Node = GenericNode<String>;

impl<T: std::fmt::Debug> std::fmt::Debug for GenericNode<T> {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        if f.alternate() {
            f.debug_struct("Node")
                .field("value", &self.value)
                .field("left", &self.left)
                .field("right", &self.left)
                .finish()
        } else {
            f.debug_struct("Node")
                .field("value", &self.value)
                .field("left", &"...")
                .field("right", &"...")
                .finish()
        }
    }
}

/// Implémentation du parseur récursif de fichier `.test`
impl Node {
    pub fn parse(s: &str) -> (Option<Box<Self>>, &str) {
        let first_token = s.find(&['(', '/'][..]).unwrap();
        let s = &s[first_token..];

        match s.chars().next() {
            Some('/') => (None, &s[1..]),
            Some('(') => {
                let s = &s[1..];
                let second_token = s.find(&['(', '/', ')'][..]).unwrap();
                let value = String::from(s[0..second_token].trim());
                let s = &s[second_token..];

                match s.chars().next() {
                    // Branch
                    Some('(') | Some('/') => {
                        let (left, next) = Node::parse(s);

                        let next_token = next.find(&['(', ')', '/'][..]).unwrap();

                        if next[next_token..].chars().next() == Some(')') {
                            return (
                                Some(Box::new(Node {
                                    value,
                                    left,
                                    right: None,
                                })),
                                &next[(next_token + 1)..],
                            );
                        }

                        let (right, next) = Node::parse(next);
                        let closing = next.find(')').unwrap();
                        (
                            Some(Box::new(Node { value, left, right })),
                            &next[(closing + 1)..],
                        )
                    }
                    // Leaf
                    Some(')') => (
                        Some(Box::new(Node {
                            value,
                            left: None,
                            right: None,
                        })),
                        &s[1..],
                    ),
                    _ => unreachable!(),
                }
            }
            _ => unreachable!(),
        }
    }
}
