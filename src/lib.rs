use std::result::Result;
use std::ops::Drop;

use std::ffi::CString;
use std::os::raw::c_char;

use std::ptr;

pub enum MWindow {}

extern { 
	fn m_init();
	fn m_quit();

	fn m_get_error() -> *mut c_char;

	fn m_window_create(w: u32, h: u32) -> *mut MWindow;
	fn m_window_destroy(win: *mut MWindow);
	fn m_window_get_size(win: *const MWindow, w: *mut u32, h: *mut u32);
	fn m_window_update(win: *mut MWindow);
	fn m_window_set_pixel(win: *mut MWindow, x: u32, y: u32, color: u32);
	fn m_window_get_pixel(win: *const MWindow, x: u32, y: u32) -> u32;

	fn m_is_closed() -> u32;

	fn m_sleep(ms: u32);
	fn m_get_ticks() -> u32;
}

pub fn init() {
	unsafe { m_init(); }
}

pub fn quit() {
	unsafe { m_quit(); }
}

fn get_error() -> CString {
	unsafe { CString::from_raw(m_get_error()) }
}

pub struct Window {
	win: *mut MWindow,
}

impl Window {
	pub fn new(w: u32, h: u32) -> Result<Window, CString> {
		let winptr;
		unsafe { winptr = m_window_create(w, h); }
		if winptr == ptr::null_mut() {
			return Err(get_error());
		}
		Ok(Window { win: winptr })
	}
}

impl Drop for Window {
	fn drop(&mut self) {
		unsafe { m_window_destroy(self.win); }
	}
}

impl Window {
	pub fn get_size(&self) -> (u32, u32) {
		let mut w: u32 = 0;
		let mut h: u32 = 0;
		unsafe { m_window_get_size(self.win, &mut w, &mut h); }
		(w, h)
	}

	pub fn update(&mut self) {
		unsafe { m_window_update(self.win); }
	}

	pub fn set_pixel(&mut self, x: u32, y: u32, color: u32) {
		unsafe { m_window_set_pixel(self.win, x, y, color); }
	}

	pub fn get_pixel(&mut self, x: u32, y: u32) -> u32 {
		unsafe { m_window_get_pixel(self.win, x, y) }
	}	
}

pub fn is_closed() -> bool {
	unsafe { m_is_closed() > 0 }
}

pub fn sleep(ms: u32) {
	unsafe { m_sleep(ms); }
}

pub fn get_ticks() -> u32 {
	unsafe { m_get_ticks() }
}
