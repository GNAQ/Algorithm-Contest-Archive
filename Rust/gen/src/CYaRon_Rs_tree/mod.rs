// TODO:
// implement the weighted tree generation algorithm

pub use rand::Rng;
pub use rand::prelude::*;

enum TreeGenMethod
{
    RandFa,
    RandPrufer,
}

enum TreeIsWeighted
{
	Unweighted,
	Weighted,
}

// TODO:
// Implement generic type for tree weight
struct TreeType<WeightType>
{
    tree_size: usize,
    edge: Vec<Vec<(u32, WeightType)>>,
    edge_unord: Vec<(u32, u32, WeightType)>,
    fa: Vec<u32>,
	node_v: Vec<WeightType>,
    gen_method: TreeGenMethod,
	is_weighted: TreeIsWeighted,
}



// TODO:
fn generate_tree <InpWeightType>
	(node_size: u32, inp_gen_method: TreeGenMethod,
	 inp_is_weighted: TreeIsWeighted) -> TreeType<InpWeightType>
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
    let mut result = TreeType::<InpWeightType>
    {
        tree_size: node_size as usize,
        gen_method: TreeGenMethod::RandFa,
		
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
        TreeGenMethod::RandFa =>
        {
            result.fa.push(0); // 1 is the root 
            for node in 2..node_size
            {
                result.fa.push(rng_gen.gen_range(1, node));
                let this_node_fa = result.fa[node as usize];
                result.edge_unord.push((this_node_fa, node));
                result.edge[this_node_fa as usize].push(node);
                result.edge[node as usize].push(this_node_fa);
            }
        },
        TreeGenMethod::RandPrufer =>
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
