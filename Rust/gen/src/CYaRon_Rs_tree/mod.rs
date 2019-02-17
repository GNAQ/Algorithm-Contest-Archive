// TODO:
// implement the weighted tree generation algorithm

pub use rand::Rng;
pub use std::io;
pub use std::collections::HashMap;

/// # 树的生成方法
/// 参见下方解释

pub enum GenMethod
{
	/// 在已经决定父亲结点的列表中随机父亲结点
	/// 
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `FixedRoot, BeginIndex` 参数
	/// 
	/// 默认为 `FixedRoot = 1, BeginIndex = 1`
    RandFa,
	/// 随机树的 `Prufer` 序列
	/// 
	/// 只接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `BeginIndex` 参数
	/// 
	/// 默认为 `BeginIndex = 1`
    RandPrufer,
	/// 生成一个花形树，既树深为 2 、所有叶子结点的父亲为树根的树
	/// 
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `FixedRoot, BeginIndex` 参数
	/// 
	/// 默认为 `FixedRoot = 1, BeginIndex = 1`
	/// 
	/// 初始化 `CYaRon_Rs_tree::GenOpt::FixedDep = 2`
	Flower,
	/// 生成一个链，既树深等于结点个数、所有点的度数均为 2 的树
	/// 
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `FixedRoot, BeginIndex` 参数
	/// 
	/// 默认为 `FixedRoot = 1, BeginIndex = 1`
	/// 
	/// 初始化 `CYaRon_Rs_tree::GenOpt::FixedDep` 为结点个数
	Chain,
	/// 生成一个二叉树 ( **或多叉树** )
	/// 
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `RandCh, FixedDep, FixedChNum, FixedRoot, BeginIndex` 参数
	/// 
	/// 默认为 `FixedRoot = 1, BeginIndex = 1, FixedDep = 0, FixedChNum = 2 RandCh = 0`
	/// 
	/// 使用 `FixedChNum` 指定非叶结点的儿子数上限
	/// 
	/// 使用 `RandCh = 1` 指定非叶结点生成恰好 `FixedChNum` 个儿子
	/// 
	/// 使用 `FixedDep` 指定深度上限, 根结点深度为 `1`
	Binary,
}

struct GenOpt
{
	FixedChNum: u32,
	FixedDep: u32,
	FixedRoot: i32,
	BeginIndex: i32,
	RandCh: bool,
}

enum IsWeighted
{
	Unweighted,
	Weighted,
}

// TODO:
// Implement generic type for tree weight
struct Tree<WeightType>
{
    tree_size: usize,
    edge: HashMap<u32, HashMap<u32, (u32, WeightType)>>,
    edge_unord: Vec<(u32, u32, WeightType)>,
    fa: HashMap<u32, u32>,
	node_v: HashMap<u32, WeightType>,
    gen_method: GenMethod,
	feature: GenOpt,
	is_weighted: IsWeighted,
}



// TODO:
fn gen_tree <InpWeightType>
	(node_size: u32, inp_gen_method: GenMethod, inp_gen_opt: GenOpt, 
	 inp_is_weighted: IsWeighted, (low, high): (InpWeightType, InpWeightType)) 
	-> Tree<InpWeightType>
{
    if node_size < 2
    {
        panic!("Error! 600 Tree Generation Failed : node number is less than 2");
    }
    else if node_size > 10_0000_0000 
    {
        panic!("Error! 601 Tree Generation Failed : node number is larger than 10,0000,0000");
    }
    
    // initialize the tree
    let mut result = Tree::<InpWeightType>
    {
        tree_size: node_size as usize,
        gen_method: GenMethod::RandFa,
		
        edge: Vec::new(),
        edge_unord: Vec::new(),
        fa: Vec::new()
    };
    let mut rng_gen = rand::thread_rng();
    
    {
        for _node in 1..node_size // init edge
        {
            result.edge.push(Vec::new());
        }
        result.fa.push(0); // we do not use index 0
    }
    
    // generate the tree
    match inp_gen_method
    {
		
        GenMethod::RandFa =>
        {
            gen_tree_by_rand_fa(&result, inp_gen_opt);
        },
		
		
        GenMethod::RandPrufer =>
        {
            //generate prufer sequence
            let mut prufer_seq: Vec<u32> = Vec::new();
            for _node in 1..(node_size - 2)
            {
                prufer_seq.push(rng_gen.gen_range(1, node_size));
            }
            // generate tree by prufer 
            let mut bac: Vec<u32> = Vec::new();
            bac.resize(node_size as usize, 1); // fill with 1
            for elem in prufer_seq.iter()
            {
                bac[(*elem) as usize] += 1;
            }
            
            for elem in prufer_seq.iter()
            {
                let mut min_node: u32 = 0;
                for i in &bac
                {
                    if (*i) == 1
                    {
                        min_node = *i;
                        break;
                    }
                }
                
                result.edge_unord.push((*elem, min_node));
                result.edge[(*elem) as usize].push(min_node);
                result.edge[min_node as usize].push(*elem);
                
                bac[(*elem) as usize] -= 1;
                bac[min_node as usize] -= 1;
            }
            
            for i in 1..node_size
            {
                if bac[i as usize] == 1
                {
                    for j in (i+1)..node_size
                    {
                        if bac[j as usize] == 1
                        {
                          result.edge_unord.push((i,j));
                          result.edge[i as usize].push(j);
                          result.edge[j as usize].push(i);
                          break;  
                        }
                    }
                    break;
                }
            }
        },
    };
    
    result
}

// TODO: TODO:
fn ch_index <InpTy>
	(mut given_tree: &Tree<InpTy>, inp_gen_opt: GenOpt) -> Result<(), String>
{
	
	Result::Ok(())
}

// 1 is the root if it's not fixed
fn gen_tree_by_rand_fa <InpTy> 
	(mut given_tree: &Tree<InpTy>, inp_gen_opt: GenOpt) -> Result<(), String>
{
	// useful variables
	let tsize = given_tree.tree_size as u32;
	
	if (inp_gen_opt.FixedChNum != 0) || 
	   (inp_gen_opt.FixedDep != 0) || 
	   (inp_gen_opt.FixedChNum != 0) ||
	   (inp_gen_opt.FixedRoot < inp_gen_opt.BeginIndex) ||
	   (inp_gen_opt.FixedRoot >= inp_gen_opt.BeginIndex + tsize)
	{
		return Result::Err("Error! 602 Tree Generation Filed : 
			you cannot assain illegal value(s) into GenOption with RandFa generation method".to_string());
	}
	
	
	given_tree.fa.insert(1, 0); // 1 is the root 
	let mut rng_gen = rand::thread_rng(); // random generator
	for idx in 2..tsize
	{
		given_tree.fa.insert(idx, rng_gen.gen_range(1, idx));
		let this_node_fa = given_tree.fa.get(&idx);
		given_tree.edge_unord.push((this_node_fa, idx));
		given_tree.edge[this_node_fa as usize].push(idx);
		given_tree.edge[idx as usize].push(this_node_fa);
	}
	
	Result::Ok(())
}

fn rand_weight()
{
	
}