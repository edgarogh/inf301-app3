#[cfg(feature = "ents")]
mod ents;
#[cfg(feature = "hero")]
mod hero;
mod node;

use appolab::AppoLabConnection;

fn open_connection() -> AppoLabConnection {
    let (mut connection, _) = AppoLabConnection::open().unwrap();
    connection.set_debug_mode(true);

    connection
        .send_receive(&format!(
            "login {}",
            std::env::var("APPOLAB_CREDS").unwrap()
        ))
        .unwrap();

    connection
}

fn main() {
    #[cfg(feature = "ents")]
    {
        println!("=== ENTS ===");

        let mut connection = open_connection();

        connection.send_receive("load ents").unwrap();
        connection.send_receive("start").unwrap();

        connection.send_receive(ents::ents_password()).unwrap();
    }

    #[cfg(feature = "hero")]
    {
        println!("=== HERO ===");

        let connection = open_connection();

        hero::hero_main(connection)
    }
}
