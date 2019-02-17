use rand::prelude::*;
use rand::Rng;

pub fn gen_f64(low: f64, high: f64) -> f64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}
pub fn gen_i32(low: i32, high: i32) -> i32
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}
pub fn gen_i64(low: i64, high: i64) -> i64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}
pub fn gen_u32(low: u32, high: u32) -> u32
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}
pub fn gen_u64(low: u64, high: u64) -> u64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
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