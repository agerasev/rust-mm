use std::result::Result;
use std::ops::Drop;
use std::ffi::CString;
use std::ptr;

use context::Context as Context;

enum MWindow {}

extern {
	fn m_window_create(w: u32, h: u32) -> *mut MWindow;
	fn m_window_destroy(win: *mut MWindow);
	fn m_window_get_size(win: *const MWindow, w: *mut u32, h: *mut u32);
	fn m_window_update(win: *mut MWindow) -> u32;
	fn m_window_set_pixel(win: *mut MWindow, x: u32, y: u32, color: u32);
	fn m_window_get_pixel(win: *const MWindow, x: u32, y: u32) -> u32;
}

pub struct Window<'a> {
	ctx: &'a Context,
	win: *mut MWindow,
}

impl<'a> Window<'a> {
	pub fn new(ctx: &Context, w: u32, h: u32) -> Result<Window, CString> {
		let winptr;
		unsafe { winptr = m_window_create(w, h); }
		if winptr == ptr::null_mut() {
			return Err(ctx.get_error());
		}
		Ok(Window { ctx: ctx, win: winptr })
	}
}

impl<'a> Drop for Window<'a> {
	fn drop(&mut self) {
		unsafe { m_window_destroy(self.win); }
	}
}

impl<'a> Window<'a> {
	pub fn get_size(&self) -> (u32, u32) {
		let mut w: u32 = 0;
		let mut h: u32 = 0;
		unsafe { m_window_get_size(self.win, &mut w, &mut h); }
		(w, h)
	}

	pub fn update(&mut self) {
		let status = unsafe { m_window_update(self.win) };
		if status != 0 {
			panic!(self.ctx.get_error());
		}
	}

	pub fn set_pixel(&mut self, x: u32, y: u32, color: u32) {
		unsafe { m_window_set_pixel(self.win, x, y, color); }
	}

	pub fn get_pixel(&mut self, x: u32, y: u32) -> u32 {
		unsafe { m_window_get_pixel(self.win, x, y) }
	}

	pub fn get_error(&self) -> CString {
		self.ctx.get_error()
	}
}
