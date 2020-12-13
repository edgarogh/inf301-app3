use crate::node::Node;
use std::collections::VecDeque;

/// Structure utilitaire permettant un parcours en largeur très pratique. Cette structure "englobe"
/// un [nœud][Node] (dans une queue) et comme elle implémente le trait [Iterator][Iterator], on
/// peut par exemple utiliser des boucles `for` dessus et s'en servir dans à peu près n'importe quel
/// contexte où les itérateurs sont supportés.
struct Width<'a> {
    queue: VecDeque<&'a Node>,
}

impl<'a> Width<'a> {
    fn new(node: &'a Node) -> Self {
        let mut queue = VecDeque::new();

        queue.push_back(node);

        Self { queue }
    }
}

impl<'a> Iterator for Width<'a> {
    /// Cet itérateur est conçu pour renvoyer des références vers des nœuds
    type Item = &'a Node;

    fn next(&mut self) -> Option<Self::Item> {
        let popped = self.queue.pop_front()?;

        if let Some(left) = &popped.left {
            self.queue.push_back(&left);
        }

        if let Some(right) = &popped.right {
            self.queue.push_back(&right);
        }

        Some(popped)
    }
}

pub fn ents_password() -> String {
    let tree = std::fs::read_to_string("ents.test").unwrap();
    let tree = Node::parse(&tree).0;
    let tree = *tree.unwrap();

    let mut width = Width::new(&tree);

    println!(
        "@ents: prefix = {:?}",
        width.find(|&s| s.value.contains("Eldarin")).unwrap()
    );
    let password = width
        .take(6)
        .map(|n| n.value.trim_end_matches(',').to_owned())
        .collect::<Vec<_>>()
        .join(" ");
    println!("@ents: password = {}", password);

    password
}
