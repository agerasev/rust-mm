use std::result::Result;
use std::ops::Drop;

use std::ffi::CString;
use std::os::raw::c_char;

extern { 
	fn mm_init(w: u32, h: u32) -> u32;
	fn mm_quit();

	fn mm_get_error() -> *mut c_char;

	fn mm_get_size(w: *mut u32, h: *mut u32);
	
	fn mm_update();

	fn mm_draw_pixel(x: u32, y: u32, color: u32);

	fn mm_handle() -> u32;

	fn mm_sleep(ms: u32);
	fn mm_get_ticks() -> u32;
}

fn get_error() -> CString {
	unsafe { CString::from_raw(mm_get_error()) }
}

pub struct System {}

impl System {
	pub fn new(w: u32, h: u32) -> Result<System, CString> {
		let status;
		unsafe { status = mm_init(w, h); }
		if status != 0 {
			return Err(get_error());
		}
		let sys = System {};
		Ok(sys)
	}
}

impl Drop for System {
	fn drop(&mut self) {
		unsafe { mm_quit(); }
	}
}

impl System {
	pub fn get_size(&self) -> (u32, u32) {
		let mut w: u32 = 0;
		let mut h: u32 = 0;
		unsafe { mm_get_size(&mut w, &mut h); }
		(w, h)
	}

	pub fn update(&self) {
		unsafe { mm_update(); }
	}

	pub fn draw_pixel(&self, x: u32, y: u32, color: u32) {
		unsafe { mm_draw_pixel(x, y, color); }
	}

	pub fn handle(&self) -> u32 {
		unsafe { mm_handle() }
	}

	pub fn sleep(&self, ms: u32) {
		unsafe { mm_sleep(ms); }
	}

	pub fn get_ticks(&self) -> u32 {
		unsafe { mm_get_ticks() }
	}
}