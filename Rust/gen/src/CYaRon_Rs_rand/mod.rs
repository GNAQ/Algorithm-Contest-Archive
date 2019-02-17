use rand::Rng;

/// 生成 `i32` 类型的随机数 ( 合法范围: `std::f64::MIN` 到 `std::f64::MAX` 函数**不会检查**您的输入是否超出该范围)
/// 
/// **请注意生成的范围为** `[low, high)`
/// 
/// # Examples
/// 
/// ```
/// println!("{}", CYaRon_Rs_rand::gen_f64(0.0, 1.0));
/// ```

pub fn gen_f64(low: f64, high: f64) -> f64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

/// 生成 `i32` 类型的随机数 ( 合法范围: `std::i32::MIN` 到 `std::i32::MAX` 函数**不会检查**您的输入是否超出该范围)
/// 
/// **请注意生成的范围为** `[low, high)`
/// 
/// # Examples
/// 
/// ```
/// println!("{}", CYaRon_Rs_rand::gen_i32(0, 5));
/// ```

pub fn gen_i32(low: i32, high: i32) -> i32
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

/// 生成 `i64` 类型的随机数 ( 合法范围: `std::i64::MIN` 到 `std::i64::MAX` 函数**不会检查**您的输入是否超出该范围)
/// 
/// **请注意生成的范围为** `[low, high)`
/// 
/// # Examples
/// 
/// ```
/// println!("{}", CYaRon_Rs_rand::gen_i64(-1_0000_0000_0000, 5_0000_0000_0000));
/// ```

pub fn gen_i64(low: i64, high: i64) -> i64
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

/// 生成 `u32` 类型的随机数 ( 合法范围: `std::u32::MIN` 到 `std::u32::MAX` 函数**不会检查**您的输入是否超出该范围)
/// 
/// **请注意生成的范围为** `[low, high)`
/// 
/// # Examples
/// 
/// ```
/// println!("{}", CYaRon_Rs_rand::gen_u32(0, 12));
/// ```

pub fn gen_u32(low: u32, high: u32) -> u32
{
    let mut rng_gen = rand::thread_rng();
    let result = rng_gen.gen_range(low, high);
    result
}

/// 生成 `u64` 类型的随机数 ( 合法范围: `std::u64::MIN` 到 `std::u64::MAX` 函数**不会检查**您的输入是否超出该范围)
/// 
/// **请注意生成的范围为** `[low, high)`
/// 
/// # Examples
/// 
/// ```
/// println!("{}", CYaRon_Rs_rand::gen_u64(0, 5_0000_0000_0000));
/// ```

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