#include "ppu/types.h"
#include "engine/camera.h"
#include "engine/draw_screen.h"
#include "engine/sprite_controller.h"
#include "engine/player_controller.h"

#include "input.h"

void hh_player_actions() {
	static hh_entity player={
		.hp = 4,
		.speed = 6,
		.is_grounded = false,
		.pos = (vec2){32,32},
		.vel = (vec2){0,0},
		.vec = (vec2){0,0},
		.render = {
			.frame0 = 20,
			.palette = 7,
			.fam = (hh_s_ppu_loc_fam_entry){
				.horizontal_flip = false,
				.vertical_flip = false,
				.palette_index = 7,
				.tilemap_index = 2,
			}
		}
	}, player_new = {0};

	// hh_input_read();
	player.vel = (vec2){.x = (-1 * g_hh_controller_p1.dpad_left) + (1 * g_hh_controller_p1.dpad_right),
	.y = (-1 * g_hh_controller_p1.dpad_up) + (1 * g_hh_controller_p1.dpad_down) };
	// const int8_t maa = 3;
	// const int8_t mbb = -3;
	// if (g_hh_controller_p1.dpad_up)
	//
	// if (g_hh_controller_p1.dpad_down)
	//
	// if (g_hh_controller_p1.dpad_left) {
	// 	player.vel.x += mbb;
	// 	// g_hh_demo_balls[0].horizontal_flip = true;
	// }
	// if (g_hh_controller_p1.dpad_right) {
	// 	player.vel.x += maa;
	// 	// g_hh_demo_balls[0].horizontal_flip = true;
	// }
	if (g_hh_controller_p1.button_primary /*&& player.is_grounded*/){ //JUMP
		hh_clear_screen();
		// player.vel.y += -6;
	}
	// // // if (g_hh_controller_p1.button_secondary)

	// player.vel.y += 1; //gravity


	//END OF VECTOR CHANGES
	// player.vel.y = CLAMP(player.vel.y,-32,32);
	// player.vel.x = CLAMP(player.vel.x,-32,32);

	player_new.pos = (vec2){
		.x = player.pos.x + player.vel.x,
		.y = player.pos.y + player.vel.y,
	};



	// const uint8_t empty = 0;
	// hh_s_tiles tiles[9];
	// const vec2 tile_offset[9] = {
	// 	(vec2){-16,-16},(vec2){0,-16},(vec2){+16,-16},
	// 	(vec2){-16,0},  (vec2){0,0},  (vec2){+16,0},
	// 	(vec2){-16,+16},(vec2){0,+16},(vec2){+16,+16},
	// };
	// for (int i = 0; i < 9; i++) {
	// 	vec2 temp_pos = vec_add(player.pos, tile_offset[i]);
	// 	temp_pos =(vec2){
	// 		.x = temp_pos.x,
	// 		.y = temp_pos.y,
	// 	};
	// 	hh_s_tiles tile = {
	// 		.pos = temp_pos,
	// 		.idx = hh_world_to_tile(temp_pos)
	// 	};
	// 	if(hh_colidable(tile.idx)) {
	// 		tiles[i]=tile;
	// 		// printf(" collidable near!");
	// 	} else {
	// 		tiles[i].idx = 0;
	// 	}
	// }
	/*
	012
	345
	678
	*/
	// for (int i = 0; i < 9; i++)
	// {
	// 	if (tiles[i].idx != 0){
	// 		hh_solve_collision(tiles[i].pos, &player);
	// 	}
	// }

	// player_new.is_grounded = false;

	// // solves x collision
	// if (player.vel.x <= 0) {
	// 	if (hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 0, .y=player.pos.y + 0})) || 
	// 		hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 0, .y=player.pos.y + 15}))) {
	// 		player_new.pos.x = (player_new.pos.x & ~15) + 16,
	// 		player_new.vel.x = 0;
	// 	}
	// } else {
	// 	if (hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 16, .y=player.pos.y + 0})) || 
	// 		hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 16, .y=player.pos.y + 15}))) {
	// 		player_new.pos.x = player_new.pos.x & ~15, // <-- magic comma, NOT TOUCHY
	// 		player_new.vel.x = 0;
	// 	}
	// }

	// //solves y collision
	// if (player.vel.y <= 0) {
	// 	if (hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 0, .y=player_new.pos.y + 0})) || 
	// 		hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 0, .y=player_new.pos.y + 15}))) {
	// 		player_new.pos.y = (player_new.pos.y & ~15) + 16,
	// 		player_new.vel.y = 0;
	// 	}
	// } else {
	// 	if (hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 0, .y=player_new.pos.y + 16})) || 
	// 		hh_colidable(hh_world_to_tile((vec2){.x=player_new.pos.x + 16, .y=player_new.pos.y + 15}))) {
	// 		player_new.pos.y = player_new.pos.y & ~15,
	// 		player_new.vel.y = 0;
	// 		player_new.is_grounded = true;
	// 	}
	// }

	player = player_new;

	vec_cor cam_pos;//value in tiles
	// cam_pos = (vec2){0,0};
	cam_pos = hh_update_camera(player.pos,(vec2){0,0},(vec2){.x=20*16,.y=30*16});//TODO: remove magic number(s)
	// printf("%i, %i:%i, %i\n",player.pos.x,player.pos.y,cam_pos.x,cam_pos.y);
	hh_draw_screen(cam_pos);
	// update player sprite on ppu
	player.render.fam.position_x = (player.pos.x-cam_pos.x);
	player.render.fam.position_y = (player.pos.y-cam_pos.y);


	player.render.fam.tilemap_index = 2;//TODO: these two lines should be redundant
	player.render.fam.palette_index = 7;
	hh_ppu_update_foreground(0, player.render.fam);

}

