#[allow(dead_code)]
#[allow(unused_imports)]
#[allow(non_snake_case)]

// modules
pub use std::io;
pub use std::io::Write;
pub use std::vec;
pub use std::io::ErrorKind;
pub use rand::Rng;

pub use CYaRon_Rs_rand::*;
pub use CYaRon_Rs_tree::*;
pub use CYaRon_Rs_file::*;

// mods
/// **生成随机数、序列等**
pub mod CYaRon_Rs_rand;
/// **生成、修改和输出各种树**
pub mod CYaRon_Rs_tree;
/// **执行文件操作**
pub mod CYaRon_Rs_file;
pub mod CYaRon_Rs_num;

// TODO: 
// 定精度浮点数 ftoi

fn main()
{
    reset_file_content("dat.in".to_string());
    
    let mut file_buf = OpenOptions::new()
        .append(true)
        .read(true)
        .create(true)
        .open("dat.in")
        .expect("Open file failed");
        
    
    
    
}
