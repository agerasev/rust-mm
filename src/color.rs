#[derive(Clone, Copy)]
pub struct Color {
	pub r: f32,
	pub g: f32,
	pub b: f32,
	pub a: f32,
}

#[macro_export]
macro_rules! color {
	($r:expr, $g:expr, $b:expr) => { Color { r: $r as f32, g: $g as f32, b: $b as f32, a: 1.0 } };
	($r:expr, $g:expr, $b:expr, $a:expr) => { Color { r: $r as f32, g: $g as f32, b: $b as f32, a: $a as f32 } };
}

impl Color {
	pub fn argb(&self) -> u32 {
		(((255.0*self.a) as u32) << 3*8) |
		(((255.0*self.r) as u32) << 2*8) |
		(((255.0*self.g) as u32) << 1*8) |
		(((255.0*self.b) as u32) << 0*8)
	}
}