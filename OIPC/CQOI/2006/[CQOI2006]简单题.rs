use std::io::*;

fn main()
{
    let mut input_str = String::new();
    stdin().read_line(&mut input_str).unwrap();
    let m: i32;
    let n: i32;
    
    {
        let mut input_div = input_str.trim().split(' ');
        n = input_div.next().unwrap().parse().unwrap();
        m = input_div.next().unwrap().parse().unwrap();
    }
    
    let mut seq: Vec<i32> = Vec::new();
    for _i in 1..n+2 { seq.push(0); }
    
    for _i in 1..m+1 
    {
        input_str.clear();
        stdin().read_line(&mut input_str).unwrap();
        let mut input_div = input_str.trim().split(' ');
        
        let opt: i32 = input_div.next().unwrap().parse().unwrap();
        if opt == 1
        {
            let lx: i32 = input_div.next().unwrap().parse().unwrap();
            let rx: i32 = input_div.next().unwrap().parse().unwrap();
            
            upd(n, lx, &mut seq); upd(n, rx+1, &mut seq);
        }
        else
        {
            let pos = input_div.next().unwrap().parse().unwrap();
            let res = qry(pos, &seq);
            println!("{}", res);
        }
    }
}

fn upd(n: i32, mut pos: i32, seq: &mut Vec<i32>)
{
    while pos <= n
    {
        seq[pos as usize] ^= 1;
        pos += pos & ( pos ^ (pos-1) );
    }
}

fn qry(mut pos: i32, seq: &Vec<i32>) -> i32
{
    let mut res = 0;
    while pos > 0
    {
        res ^= seq[pos as usize];
        pos -= pos & ( pos ^ (pos-1) );
    }
    res
}