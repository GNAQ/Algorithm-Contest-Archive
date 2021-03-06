use std::io::*;

fn main()
{
    let n: i64;
    let mut inp_str = String::new();
    
    stdin().read_line(&mut inp_str).expect("Read Err");
    n = inp_str.trim().parse().unwrap();
    
    let mut seq: Vec<i64> = Vec::new();
    for _i in 1..n + 1
    {
        inp_str.clear();
        stdin().read_line(&mut inp_str).expect("Read Err");
        seq.push(inp_str.trim().parse().unwrap());
    }
    
    let mut avg: i64 = 0;
    for v in &seq
    {
        avg += *v;
    }
    avg/=n;
    for v in &mut seq
    {
        *v -= avg;
    }
    for i in 1..n as usize
    {
        seq[i] += seq[i - 1];
    }
    
    seq.sort();
    
    let midv = 
    {
        if n % 2 == 0 
        {
            n >> 1
        }
        else
        {
            (n + 1) >> 1
        }
    } - 1;
    let mid = seq[midv as usize];
    let mut ans: i64 = 0;
    
    for v in &seq
    {
        ans += (*v - mid).abs();
    }
    
    println!("{}", ans);
}