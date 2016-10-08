//pub use hello;

extern { 
	fn mmc_init();
	fn mmc_quit();
	fn mmc_sleep(ms: u32);
	fn mmc_handle() -> u32;
}

pub fn init() {
	unsafe { mmc_init(); }
}

pub fn quit() {
	unsafe { mmc_quit(); }
}

pub fn sleep(ms: u32) {
	unsafe { mmc_sleep(ms); }
}

pub fn handle() -> u32 {
	let status;
	unsafe { status = mmc_handle(); }
	status
}