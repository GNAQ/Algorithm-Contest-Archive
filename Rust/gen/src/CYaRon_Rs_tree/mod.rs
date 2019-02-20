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
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `fixed_root, begin_index` 参数
	/// 
	/// 默认为 `fixed_root = 1, begin_index = 1`
    RandFa,
	/// 随机树的 `Prufer` 序列
	/// 
	/// 只接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `begin_index` 参数
	/// 
	/// 默认为 `begin_index = 1`
    RandPrufer,
	/// 生成一个花形树，既树深为 2 、所有叶子结点的父亲为树根的树
	/// 
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `fixed_root, begin_index` 参数
	/// 
	/// 默认为 `fixed_root = 1, begin_index = 1`
	/// 
	/// 初始化 `CYaRon_Rs_tree::GenOpt::fixed_dep = 2`
	Flower,
	/// 生成一个链，既树深等于结点个数、所有点的度数均为 2 的树
	/// 
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `fixed_root, begin_index` 参数
	/// 
	/// 默认为 `fixed_root = 1, begin_index = 1`
	/// 
	/// 初始化 `CYaRon_Rs_tree::GenOpt::fixed_dep` 为结点个数
	Chain,
	/// 生成一个二叉树 ( **或多叉树** )
	/// 
	/// 接受指定 `CYaRon_Rs_tree::GenOpt` 内的 `fixed_ch_num, fixed_dep, fixed_ch_limit, fixed_root, begin_index` 参数
	/// 
	/// 默认为 `fixed_root = 1, begin_index = 1, fixed_dep = 0, fixed_ch_limit = 2 fixed_ch_num = 0`
	/// 
	/// 使用 `fixed_ch_limit` 指定非叶结点的儿子数上限
	/// 
	/// 使用 `fixed_ch_num = true` 指定非叶结点生成恰好 `fixed_ch_limit` 个儿子
	/// 
	/// 使用 `fixed_dep` 指定深度上限, 根结点深度为 `1`
	Binary,
}

pub struct GenOpt
{
	fixed_ch_limit: u32,
	fixed_dep: u32,
	fixed_root: i32,
	begin_index: i32,
	fixed_ch_num: bool,
}

pub enum IsWeighted
{
	Unweighted,
	NodeWeighted,
    EdgeWeighted,
    Both,
}

// TODO:
// Implement generic type for tree weight
pub struct Tree<WeightType>
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

impl GenOpt
{
    /// 构建一个新的 Tree generate option (树的生成附加选项)
    /// 
    /// 成员变量的默认初始化如下:
    /// 
    /// ```
    /// begin_index: 1
    /// fixed_root: 1
    /// fixed_ch_limit: 0
    /// fixed_ch_num: false
    /// fixed_dep: 0
    /// ```
    /// 
    /// # Example
    /// 
    /// ```
    /// use CYaRon_Rs_tree;
    /// 
    /// let mut tree1_genopt = GenOpt::new();
    /// ```
            
    fn new() -> GenOpt 
    {
        GenOpt
        {
            begin_index: 1,
            fixed_root: 1,
            fixed_ch_limit: 0,
            fixed_ch_num: false,
            fixed_dep: 0,
        }
    }
}


// TODO:

/// **生成一棵树**
/// 
/// 参数列表: 
/// 
/// `node_size` : 树的点数 
/// 
/// `inp_gen_method` : 生成方法 (参见 `CYaRon_Rs_tree::GenMethod` ) 
/// 
/// `inp_gen_opt` : 附加生成选项 (参见 `CYaRon_Rs_tree::GenOpt` ) 
/// 
/// `inp_is_weighted` : 是否带权 (参见 `CYaRon_Rs_tree::IsWeighted` ) 
/// 
/// `(nlow, nhigh)` : 点权值随机下界、上界, 无权树忽略此参数 (请注意 **不会取到上界** 随机算法实际调用 `CYaRon_Rs_rand::gen_type` )
/// 
/// `(elow, ehigh)` : 边权值随机下界、上界, 无权树忽略此参数 (请注意 **不会取到上界** 随机算法实际调用 `CYaRon_Rs_rand::gen_type` )
///
/// # Example
/// 
/// ```
/// use CYaRon_Rs_tree;
/// 
/// let gen_opt = GenOpt::new();
/// match gen_tree(1, 
///                GenMethod::RandFa,
///                GenOpt::new(), 
///                IsWeighted::UnWeighted, 
///                (0,0),
///                (0,0)
///                )
/// ```

pub fn gen_tree <InpTy>
	(node_size: u32, 
     inp_gen_method: GenMethod, 
     inp_gen_opt: GenOpt, 
	 inp_is_weighted: IsWeighted, 
     (nlow, nhigh): (InpTy, InpTy), 
     (elow, ehigh): (InpTy, InpTy)) 
	-> Result<Tree<InpTy>, String>
{
    // throw exception
    if node_size < 2
    {
        return Result::Err(
            "Error! 600 Tree Generation Failed : node number is less than 2".to_string());
    }
    else if node_size > 10_0000_0000 
    {
        return Result::Err(
            "Error! 601 Tree Generation Failed : node number is larger than 10,0000,0000".to_string());
    }
    
    // initialize the tree
    let mut result = Tree::<InpTy>
    {
        tree_size: node_size as usize,
        gen_method: inp_gen_method,
        feature: inp_gen_opt,
        is_weighted: inp_is_weighted,
		
        // member data sturctures
        node_v: HashMap::new(),
        fa: HashMap::new(),
        edge: HashMap::new(),
        edge_unord: Vec::new(),
    };
    // random generator
    let mut rng_gen = rand::thread_rng();
    
    // generate the tree
    match inp_gen_method
    {
		
        GenMethod::RandFa =>
        {
            gen_tree_by_rand_fa(&result, inp_gen_opt);
            
        },
		
		
        GenMethod::RandPrufer =>
        {
            gen_tree_by_rand_prufer(&result, inp_gen_opt);
            
        },
    };
    
    match inp_is_weighted
    {
        IsWeighted::NodeWeighted =>
        {
            
        },
        IsWeighted::EdgeWeighted =>
        {
            
        },
        IsWeighted::Both =>
        {
            
        },
    }
    
    Result::Ok(result)
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
	
	if (inp_gen_opt.fixed_ch_limit != 0) || 
	   (inp_gen_opt.fixed_dep != 0) || 
	   (inp_gen_opt.fixed_ch_limit != 0) ||
	   (inp_gen_opt.fixed_root < inp_gen_opt.begin_index) ||
	   (inp_gen_opt.fixed_root >= inp_gen_opt.begin_index + (tsize as i32))
	{
		return Result::Err("Error! 602 Tree Generation Filed : 
			you cannot assain illegal value(s) into GenOption 
            with RandFa generation method".to_string());
	}
	
	
	given_tree.fa.insert(1, 0); // 1 is the root 
	let mut rng_gen = rand::thread_rng(); // random generator
	for idx in 2..=tsize as u32
	{
		given_tree.fa.insert(idx, rng_gen.gen_range(1, idx));
		let this_node_fa = given_tree.fa.get(&idx);
		given_tree.edge_unord.push((this_node_fa, idx));
		given_tree.edge[this_node_fa as usize].push(idx);
		given_tree.edge[idx as usize].push(this_node_fa);
	}
	
	Result::Ok(())
}

fn gen_tree_by_rand_prufer <InpTy>
    (mut given_tree: &Tree<InpTy>, inp_gen_opt: GenOpt) ->Result<(), String>
{
    let tsize = given_tree.tree_size as u32;
	if (inp_gen_opt.fixed_ch_limit != 0) || 
	   (inp_gen_opt.fixed_dep != 0) || 
	   (inp_gen_opt.fixed_ch_limit != 0) ||
	   (inp_gen_opt.fixed_root < inp_gen_opt.begin_index) ||
	   (inp_gen_opt.fixed_root >= inp_gen_opt.begin_index + (tsize as i32))
	{
		return Result::Err("Error! 603 Tree Generation Filed : 
			you cannot assain illegal value(s) into GenOption 
            with RandPrufer generation method".to_string());
	}
    
    
    let mut rng_gen = rand::thread_rng();
    //generate prufer sequence
    let mut prufer_seq: Vec<u32> = Vec::new();
    for _node in 1..=(node_size - 2)
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
    
    for i in 1..=node_size
    {
        if bac[i as usize] == 1
        {
            for j in (i+1)..=node_size
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
    
    Result::Ok(())
}

fn rand_weight <InpTy> 
    (mut given_tree: &Tree<InpTy>, low: InpTy, high: InpTy) -> Result<(), String>
{
    
    
    Result::Ok(())
}