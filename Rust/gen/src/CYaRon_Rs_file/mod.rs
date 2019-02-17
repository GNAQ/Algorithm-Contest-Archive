// FINISHED
pub use std::fs::{File, OpenOptions};
pub use std::io::{self, ErrorKind};

///
/// 

pub fn reset_file_content(file_name: String)
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
                Err(error0) => panic!("Error 202 removing file {:?}", error0),
            }
        },
        Err(error1) => match error1.kind()
        {
            ErrorKind::NotFound => match File::create(& file_name)
            {
                Ok(created_file) => created_file,
                Err(error2) => panic!("Error 201 creating file {:?}", error2),
            },
            other_error => panic!("Error 200 opening file {:?}", other_error),
        },
    };
}

// TODO:
// 