use std::io::*;

fn main()
{
    let t: i32;
    let mut inp_str = String::new();
    
    stdin().read_line(&mut inp_str).unwrap();
    
    t = inp_str.trim().parse().unwrap();
    
    for _q in 1..t+1
    {
        let n: i32;
        let mut seq: Vec<i32> = Vec::new();
        
        inp_str.clear();
        stdin().read_line(&mut inp_str).unwrap();
        n = inp_str.trim().parse().unwrap();
        
        inp_str.clear();
        stdin().read_line(&mut inp_str).unwrap();
        let mut inp_div = inp_str.trim().split(' ');
        for _i in 1..n+1
        {
            seq.push(inp_div.next().unwrap().parse().unwrap());
        }
        
        let mut ans: i32 = 0;
        for i in seq
        {
            ans ^= i;
        }
        
        if ans != 0 
        {
            println!("Yes");
        }
        else
        {
            println!("No");
        }
    }
}