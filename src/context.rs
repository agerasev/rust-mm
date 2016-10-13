use std::result::Result;
use std::ops::Drop;
use std::ffi::CString;
use std::os::raw::c_char;

extern { 
	fn m_init() -> u32;
	fn m_quit();

	fn m_get_error() -> *mut c_char;

	fn m_is_closed() -> u32;

	fn m_sleep(ms: u32);
	fn m_get_ticks() -> u32;
}

pub struct Context {}

impl Context {
	pub fn acquire() -> Result<Context, CString> {
		let status;
		unsafe { status = m_init(); }
		if status != 0 {
			return Err(unsafe { CString::from_raw(m_get_error()) });
		}
		Ok(Context {})
	}
}

impl Drop for Context {
	fn drop(&mut self) {
		unsafe { m_quit(); }
	}
}

impl Context {
	pub fn get_error(&self) -> CString {
		unsafe { CString::from_raw(m_get_error()) }
	}

	pub fn is_closed(&self) -> bool {
		unsafe { m_is_closed() > 0 }
	}

	pub fn sleep(&self, ms: u32) {
		unsafe { m_sleep(ms); }
	}

	pub fn get_ticks(&self) -> u32 {
		unsafe { m_get_ticks() }
	}
}
