use std::process::Command;
use std::env;

fn main() {
	let out_dir = env::var("OUT_DIR").unwrap();

	let output = Command::new("mingw32-make.exe").arg(&"all").output().unwrap();
	if !output.status.success() {
		panic!("status: {}\n{}\n{}", output.status, 
			String::from_utf8_lossy(output.stdout.as_slice()),
			String::from_utf8_lossy(output.stderr.as_slice())
		);
	}

	println!("cargo:rustc-link-search=native={}", out_dir);
	println!("cargo:rustc-link-lib=static=mmc");
	println!("cargo:rustc-link-search=native=C:\\devel\\lib\\SDL2\\lib");
	println!("cargo:rustc-link-lib=SDL2");
}