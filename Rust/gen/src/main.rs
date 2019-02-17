#[allow(dead_code)]
#[allow(unused_imports)]
#[allow(non_snake_case)]

// modules
pub use std::io::*;
pub use std::io::Write;
pub use std::vec::*;
pub use std::io::ErrorKind;
pub use std::vec::*;
pub use rand::Rng;
pub use rand::prelude::*;

pub use CYaRon_Rs_rand::*;
pub use CYaRon_Rs_tree::*;
pub use CYaRon_Rs_file::*;

// mods
pub mod CYaRon_Rs_rand;
pub mod CYaRon_Rs_tree;
pub mod CYaRon_Rs_file;

fn main()
{
    reset_file_content("dat.in".to_string());
    
    let mut file_buf = OpenOptions::new()
        .append(true)
        .read(true)
        .create(true)
        .open("dat.in")
        .expect("Open file failed");
    
    writeln!(file_buf, "{}", gen_f64(0.0 as f64, 1.0 as f64)).unwrap();
    writeln!(file_buf, "{}", gen_i64(1 as i64, 1_0000_0000_0000 as i64)).unwrap();
}


