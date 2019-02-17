#[allow(unused_marcos)]
use std::io::*;
use std::fs::File;
use std::fs::OpenOptions;
use std::io::Write;
use std::io::prelude::*;
use std::vec::*;
use std::io::ErrorKind;
use std::vec::*;
use rand::prelude::*;
use rand::Rng;


// FIXME:
// cannot reset the file context when open (output) files

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

// FINISHED
fn reset_file_content(file_name: String)
{
    let file_buf = File::open(& file_name);
    
    match file_buf
    {
        Ok(existed_file) => 
        {
            drop(existed_file);
            std::fs::remove_file(& file_name).unwrap();
            match File::create(& file_name)
            {
                Ok(replaced_file) => replaced_file,
                Err(error0) => panic!("Error removing file {:?}", error0),
            }
        },
        Err(error1) => match error1.kind()
        {
            ErrorKind::NotFound => match File::create(& file_name)
            {
                Ok(created_file) => created_file,
                Err(error2) => panic!("Error creating file {:?}", error2),
            },
            other_error => panic!("Error opening file {:?}", other_error),
        },
    };
}

fn gen_f64(low: f64, high: f64) -> f64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

fn gen_i32(low: i32, high: i32) -> i32
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

fn gen_i64(low: i64, high: i64) -> i64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

fn gen_u32(low: u32, high: u32) -> u32
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

fn gen_u64(low: u64, high: u64) -> u64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

// TODO:
// implement the tree generation algorithm

enum TreeGenMethod
{
    RandFa,
    RandPurfer,
}

struct UnweightedTree
{
    tree_size: usize,
    edge: Vec<Vec<u32>>,
    fa: Vec<u32>,
    gen_method: TreeGenMethod,
}

// TODO:
fn generate_tree_unweighted(node_size: u32) -> UnweightedTree
{
    // initialize the tree
    let mut result = UnweightedTree 
    {
        tree_size: node_size as usize,
        gen_method: TreeGenMethod::RandFa,
        edge: Vec::new(),
        fa: Vec::new()
    };
    
    let mut rng_gen = rand::thread_rng();
    
    result.fa.push(0); // we do not use index 0
    result.fa.push(0); // 1 is the root 
    for node in 2..node_size
    {
        result.fa.push(rng_gen.gen_range(1, node));
    }
    
    
    result
}


// generate a random sequence with contigious 
// FIXME:
// implement a trait
/*
fn generate_randint_seq <inp_typ> 
    (SeqSize: usize, low: inp_typ, high: inp_typ) -> Vec<inp_typ>
{
    let mut rng_gen = rand::thread_rng();
    // FIXME:
    let mut result: Vec<inp_typ>::new();
    
    // generate a sequence
    for i in low..high
    {
        result.push(i);
    }
    // randomly shuffle 
    result.shuffle(&mut rng_gen);
    result
    
}
*/