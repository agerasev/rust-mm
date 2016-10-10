mod color;
pub use color::Color;

extern { 
	fn mmc_init(w: u32, h: u32) -> u32;
	fn mmc_quit();

	fn mmc_get_size(w: *mut u32, h: *mut u32);

	// fn mmc_clear();
	// fn mmc_present();

	fn mmc_update();

	fn mmc_draw_point(x: u32, y: u32);
	fn mmc_set_color(r: u8, g: u8, b: u8, a: u8);

	fn mmc_sleep(ms: u32);
	fn mmc_handle() -> u32;
}

pub fn init(w: u32, h: u32) -> u32 {
	unsafe { mmc_init(w, h) }
}

pub fn quit() {
	unsafe { mmc_quit(); }
}

pub fn get_size() -> (u32, u32) {
	let mut w: u32 = 0;
	let mut h: u32 = 0;
	unsafe { mmc_get_size(&mut w, &mut h); }
	(w, h)
}

/*
pub fn clear() {
	unsafe { mmc_clear(); }
}

pub fn present() {
	unsafe { mmc_present(); }
}
*/
pub fn update() {
	unsafe { mmc_update(); }
}

pub fn draw_point(x: u32, y: u32) {
	unsafe { mmc_draw_point(x, y); }
}

fn f32_to_u8(v: f32) -> u8 {
	let nv: f32 = if v >= 0.0 && v <= 1.0 { v } else if v > 1.0 { 1.0 } else { 0.0 };
	(255.0*nv) as u8
}

pub fn set_color(c: Color) {
	let f = f32_to_u8;
	unsafe { mmc_set_color(f(c.r), f(c.g), f(c.b), f(c.a)); }
}

pub fn sleep(ms: u32) {
	unsafe { mmc_sleep(ms); }
}

pub fn handle() -> u32 {
	let status;
	unsafe { status = mmc_handle(); }
	status
}