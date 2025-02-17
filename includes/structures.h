/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olimarti <olimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 03:24:57 by motero            #+#    #+#             */
/*   Updated: 2024/02/20 23:17:27 by olimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdint.h>
# include <stdbool.h>
# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include "colors.h"
# include "mlx_int.h"
# include "dynamic_array.h"
# include "sparse_array.h"
# include "settings.h"

/*############################################################################*/
/*                              STRUCTURES                                    */
/*############################################################################*/

/* Vector structure for 2D float vector
** Vector structure for 2D unsigned int vector
** Vector structure for 2D int vectors
** causes the compiler to set the mode for foo,
** to be 16 bytes, divided into int sized units.
** SIMD vectorrization
** https://users.ece.cmu.edu/~franzf/teaching/slides-18-645-simd.pdf
**
*/

typedef enum e_side
{
	SIDE_ON			= 0b0000,
	SIDE_LEFT		= 0b0001,
	SIDE_RIGHT		= 0b0010,
	SIDE_INTERSECT	= 0b0011,
}	t_side;

enum e_action { a_move_forward,
	a_move_backward,
	a_move_left,
	a_move_right,
	a_move_up,
	a_move_down,
	a_turn_left,
	a_turn_right,
	a_increase_sector_ceil,
	a_decrease_sector_ceil,
	a_increase_sector_floor,
	a_decrease_sector_floor,
	ACTIONS_COUNT};

typedef float			t_vector_f		__attribute__((vector_size (8)));
typedef unsigned int	t_vector_u		__attribute__((vector_size (8)));
typedef int				t_vector_i		__attribute__((vector_size (8)));

typedef int				t_v2i			__attribute__((vector_size (2
	* sizeof(int))));
typedef double			t_v2d			__attribute__((vector_size (2
	* sizeof(double))));
typedef u_int8_t		t_vector_color	__attribute__((vector_size (4
	* sizeof(u_int8_t))));
typedef u_int64_t		t_vector_color_16	__attribute__((vector_size (4
	* sizeof(u_int16_t))));
typedef double			t_v4d			__attribute__((vector_size (4
	* sizeof(double))));

typedef struct s_segment_d t_segment_d;

typedef union u_vector4d
{
	t_v4d	vec;
	struct {
		double	x;
		double	y;
		double	z;
		double	w;
	};
}	t_vector4d;

typedef union u_point2d
{
	t_v2d	vec;
	struct {
		double	x;
		double	y;
	};
}	t_point2d;

typedef union u_point2i
{
	t_v2i	vec;
	struct {
		int	x;
		int	y;
	};
}	t_point2i;

/* bpp = bits per pixel */
typedef struct s_img_data
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	t_point2i	size;
}	t_img_data;

/*############################################################################*/
/*                              	ASSETS                                    */
/*############################################################################*/

typedef enum e_ui_assets
{
	WINDOW_BASE,
	WINDOW_HEADER_INACTIVE,
	WINDOW_HEADER_RESIZABLE_INACTIVE,
	WINDOW_HEADER_RESIZABLE,
	WINDOW_HEADER,
	WINDOWS_BUTTON_FOCUS_OUTLINED,
	WINDOWS_BUTTON_FOCUS,
	WINDOWS_BUTTON_INACTIVE,
	WINDOWS_BUTTON_PRESSED_OUTLINED,
	WINDOWS_BUTTON_PRESSED,
	WINDOWS_BUTTON,
	WINDOWS_DIVIDER_LINE,
	WINDOWS_EXAMPLE_ITCHPIC,
	WINDOWS_EXAMPLE_MAIN,
	WINDOWS_EXAMPLE_POPUP,
	WINDOWS_ICONS,
	WINDOWS_INNER_FRAME_INVERTED,
	WINDOWS_INNER_FRAME,
	WINDOWS_PROGRESS_FILL,
	WINDOWS_RATIO_INACTIVE,
	WINDOWS_RATIO_SELECTED,
	WINDOWS_RATIO,
	WINDOWS_SIDEBAR_UNDERSIDE,
	WINDOWS_SLIDER_BACKGROUND,
	WINDOWS_SLIDER_HANDLE,
	WINDOWS_TOGGLE_ACTIVE,
	WINDOWS_TOGGLE_INACTIVE,
	WINDOWS_TOGGLE_SELECTED,
	BACKGROUND,
	ICON_DRAW,
	ICON_GAME,
	BAR_WITH_DRAW,
	SIDE_BAR,
	UI_ASSET_COUNT
}	t_ui_assets;

typedef enum e_game_assets
{
	MONSTER_LINE_TEXTURE,
	DUCK_TEXTURE_WALK_00,
	DUCK_TEXTURE_WALK_01,
	DUCK_TEXTURE_WALK_02,
	DUCK_TEXTURE_WALK_03,
	DUCK_TEXTURE_IDLE_00,
	DUCK_TEXTURE_IDLE_01,
	PENGUIN_TEXTURE_WALK_00,
	PENGUIN_TEXTURE_WALK_01,
	PENGUIN_TEXTURE_WALK_02,
	PENGUIN_TEXTURE_WALK_03,
	GAME_ASSET_COUNT
}	t_game_assets;


typedef enum e_texture_id
{
	TEXTURE_WALL_NORTH,
	TEXTURE_WALL_SOUTH,
	TEXTURE_WALL_EAST,
	TEXTURE_WALL_WEST,
	TEXTURE_DUCK_IDLE,
	TEXTURE_DUCK_WALK,
	TEXTURE_PENGUIN_WALK,
	TEXTURE_PENGUIN_IDLE,
	TEXTURE_COUNT
}	t_texture_id;

/* Parsing structure for CUB3D stocking information from .cub file
** a wolrd map in a 2D int array of MAPWIDTH * MAPHEIGHT
** a array  of size 4 of sprites using t_image from the mlx
** in the order from indx 0 to 3 : N, S, E, W
** a uint_32_t for the color of the floor
** a uint_32_t for the color of the ceiling
*/


#ifdef	LITTLE_ENDIAN
typedef union u_color
{
	t_vector_color rgb_color;
	u_int32_t d;
	struct
	{
		u_int8_t b;
		u_int8_t g;
		u_int8_t r;
		u_int8_t a;
	};
} t_color;

typedef union u_64_color
{
	t_vector_color_16 rgb_color;
	u_int64_t d;
	struct
	{
		u_int16_t b;
		u_int16_t g;
		u_int16_t r;
		u_int16_t a;
	};
} t_color_64;

typedef union u_color_factor
{
	t_v4d	vec;
	struct
	{
		double	b;
		double	g;
		double	r;
		double	a;
	};
}	t_color_factor;

#else

typedef union u_color
{
	t_vector_color rgb_color;
	u_int32_t d;
	struct
	{
		u_int8_t a;
		u_int8_t r;
		u_int8_t g;
		u_int8_t b;
	};
} t_color;

typedef union u_color_64
{
	t_vector_color_16 rgb_color;
	u_int64_t d;
	struct
	{
		u_int16_t a;
		u_int16_t r;
		u_int16_t g;
		u_int16_t b;
	};
} t_color_64;


typedef union u_color_factor
{
	t_v4d	vec;
	struct
	{
		double	a;
		double	r;
		double	g;
		double	b;
	};
}	t_color_factor;

#endif

/*############################################################################*/
/*                              MATRIX STRUCTURES                             */
/*############################################################################*/

typedef struct s_matrix4x4_vectorized
{
	t_vector4d	row[3];
}	t_matrix3x3;

typedef struct s_player
{
	t_vector4d	pos;
	t_vector4d	dir;
	t_vector4d	velocity;
	t_vector4d	right;
	t_vector_f	plane;
}				t_player;

typedef struct s_dda
{
	t_vector_f	ray_dir;
	t_vector_f	side_dist;
	t_vector_f	delta_dist;
	t_vector_i	map;
	t_vector_f	pos;
	t_vector_i	step;
	uint32_t	color;
	float		perp_wall_dist;
	float		tex_pos;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			hit;
	int			side;
	int			tex_y;
	int			x;
	t_vector_i	mouse;
}				t_dda;

typedef enum e_drawing_state
{
	NOT_DRAWING,
	DRAWING,
	END_DRAWING
}	t_drawing_state;

typedef enum e_update_type
{
	UPDATE = 0,
	FULL_REDRAW = 1,
	LINE_REDRAW = 2,
	NO_UPDATE = 4
}	t_update_type;

typedef enum e_modus_state
{
	MENU,
	MAP_EDITOR,
	GAMEPLAY,
	END_GAME_STATE
}	t_modus_state;

typedef enum e_img_fit_mode
{
	FIT_IMAGE_TO_CANVAS,
	FIT_CANVAS_TO_IMAGE
}	t_img_fit_mode;

typedef struct s_inputs
{
	int		action_states[ACTIONS_COUNT];
}			t_inputs;

typedef struct s_tree_node
{
	struct s_tree_node	*parent;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
	void				*data;
}	t_tree_node;


typedef struct s_circle
{
	t_vector4d	center;
	double		radius;
}				t_circle;

typedef struct s_collision_info
{
	bool			collision;
	t_vector4d		collision_normal;
}					t_collision_info;

/*############################################################################*/
/*                              CANVAS STRUCTURES                             */
/*############################################################################*/



typedef enum e_canvas_type
{
	MAP,
	UI,
	BUTTON,
	GAME,
	FINAL,
	FIN_TEMP,
	END_MARKER
}	t_canvas_type;

typedef struct s_dirty_rect
{
	t_point2d	pos;
	t_point2d	size;
}	t_dirty_rect;

typedef struct s_camera_effect_wave
{
	bool	enabled;
	double	amplitude_x;
	double	frequency_x;
	double	amplitude_y;
	double	frequency_y;
	double	offset_x;
	double	offset_y;
}	t_camera_effect_wave;

typedef struct s_camera_posterization
{
	bool		enabled;
	u_int16_t	levels;
}	t_camera_posterization;

typedef struct s_camera_effects
{
	t_camera_effect_wave	wave;
	t_camera_posterization	posterization;
}	t_camera_effects;

typedef struct s_camera
{
	t_vector4d			pos;
	t_vector4d			dir;
	t_vector4d			right;
	t_vector4d			velocity;
	double				tilt;
	double				fov;
	t_camera_effects	effects;
}				t_camera;

typedef struct s_texture
{
	t_img_data	**frames;
	bool		is_animated;
	int			frame_count;
	int			current_frame;
	size_t		ms_per_frame;
	size_t		current_time;
}	t_texture;

typedef struct s_texture_ptr
{
	int			offset;
	t_texture	*texture;
}	t_texture_ptr;


typedef struct s_texture_manager
{
	t_texture	textures[TEXTURE_COUNT];
}	t_texture_manager;


typedef struct s_spawn
{
	t_vector4d	pos;
	t_vector4d	dir;
}	t_spawn;

typedef struct s_map_data
{
	t_tree_node			*bsp;
	t_list				*segments;
	t_texture_manager	*texture_manager;
	t_color				floor_color;
	t_color				ceil_color;
	t_spawn				player_spawn;
}	t_map_data;

typedef struct s_circular_queue
{
	size_t	elem_size;
	size_t	size;
	size_t	start;
	size_t	end;
	void	*buffer;
}	t_circular_queue;

typedef struct s_canvas t_canvas;


typedef struct s_3d_render_buffers
{
	t_color				*color;
	double				*depth;
	t_vector4d			*world_pos;
	t_vector4d			*normal;
	t_color				*color_bis;
}	t_3d_render_buffers;

typedef enum e_light_type
{
	POINT_LIGHT,
	DIRECTIONAL_LIGHT
}	t_light_type;

typedef struct s_light
{
	int				id;
	t_light_type	type;
	t_vector4d		pos;
	t_vector4d		dir;
	t_color			color;
	double			intensity;
	bool			use_raycasting;
	bool			show_lens_flare;
	int				lens_flare_id;
}	t_light;

typedef struct s_light_lens_flare
{
	bool			visible;
	t_vector4d		screen_pos;
	double			intensity;
	t_color			color;
}	t_light_lens_flare;

typedef struct s_lights_data
{
	t_sparse_array		*lights;
	t_sparse_array		*lens_flare;
	t_color_factor		ambiant_light;
}	t_light_data;

typedef struct s_3d_render
{
	t_canvas			*canvas;
	double				*top_array;
	double				*bottom_array;
	t_3d_render_buffers	buffers;
	t_circular_queue	*queue;
	t_camera			*camera;
	t_map_data			*map;
	int					width;
	int					height;
	t_vector4d			middle;
	int					scale_factor_x;
	int					scale_factor_y;
	t_light_data		lights_data;
}	t_3d_render;

typedef struct s_entity_player_data
{
	t_vector4d	right;
}				t_entity_player_data;

typedef struct s_entity_penguin_data
{
	t_vector4d	right;
}				t_entity_penguin_data;

typedef struct s_entity_torch_data
{
	int				light_id;
	double			light_intensity;
	unsigned int	current_interval_duration;
	unsigned int	last_flicker_time;
	int				flicker_remaining_duration;
	unsigned int	flicker_duration;
	unsigned int	flicker_interval;
	unsigned int	flicker_intensity;
	double			flicker_interval_variance;
	double			flicker_duration_variance;
	double			flicker_intensity_variance;
}				t_entity_torch_data;

typedef struct s_entity t_entity;

typedef struct s_game_state
{
	t_camera				player_camera;
	t_sparse_array			*entities;
	t_entity				*player;
	bool					is_ready;
	double					delta_time;
	unsigned int			time_since_start;
}	t_game_state;


typedef struct s_game_data
{
	t_game_state	state;
	t_3d_render		game_view_render;
	t_map_data		map_data;
	t_inputs		*inputs;
}	t_game_data;

typedef enum e_entity_type
{
	ENTITY_DEFAULT,
	ENTITY_PLAYER,
	ENTITY_TORCH,
	ENTITY_PENGUIN
}					t_entity_type;

typedef enum e_collision_model_type
{
	COLLISION_MODEL_NONE,
	COLLISION_MODEL_STATIC_SURFACE,
	COLLISION_MODEL_DYNAMIC_CYLINDER
}	t_collision_model_type;

typedef struct s_collision_model_static_surface
{
	t_vector4d		normal;
	double			distance;
}	t_collision_model_static_surface;

typedef struct s_collision_model_dynamic_cylinder
{
	double			radius;
	double			height;
}	t_collision_model_dynamic_cylinder;

typedef struct s_collision_model
{
	t_collision_model_type	type;
	union
	{
		t_collision_model_static_surface	static_surface;
		t_collision_model_dynamic_cylinder	dynamic_cylinder;
	};
}	t_collision_model;

typedef struct s_entity_physics
{
	t_vector4d			pos;
	t_vector4d			dir;
	t_vector4d			right;
	t_vector4d			velocity;
	t_vector4d			acceleration;
	double				friction;
	t_collision_model	collision_model;
}				t_entity_physics;


typedef struct s_entity
{
	int					id;
	t_entity_type		type;
	t_entity_physics	physics;
	void				*data;
	bool				should_be_destroyed;
	void				(*update)(struct s_entity *self, t_game_data *game_data);
	void				(*draw)(struct s_entity *self, t_game_data *game_data);
	void				(*destroy)(struct s_entity *self, t_game_data *game_data);
}					t_entity;

typedef struct s_data
{
	char		**textures;
	char		**colors;
	char		***map;
}				t_data;


typedef struct s_sector_data
{
	double		floor;
	double		ceil;
	int			render_flag_id;
	t_vector4d	center;
}	t_sector_data;

typedef enum e_segment_type
{
	WALL,
	PORTAL
}	t_segment_type;


typedef struct s_wall_data
{
	int				size;
	double			height;
	t_texture_ptr	texture;
}	t_wall_data;

typedef struct s_portal_data
{
	int				size;
	int				render_flag_id;
	void			*destination;
	void			*tree_node_ptr;
	t_texture_ptr	padding_texture_top;
	t_texture_ptr	padding_texture_bottom;
}	t_portal_data;

typedef union u_wall_portal_data
{
	t_wall_data		wall;
	t_portal_data	portal;
}	t_wall_portal_data;

typedef struct s_segment_data
{
	t_segment_type		type;
	t_wall_portal_data	data;
	double				ceil;
	double				floor;
	t_vector4d			normal;
	double				size;
}	t_segment_data;

struct	s_segment_d
{
	t_vector4d		point_a;
	t_vector4d		point_b;
	t_segment_data	data;
};

typedef enum e_direction{
	NONE = 0,
	RIGHT = 1,
	DOWN = 2,
	DIAGONAL_RIGHT = 4,
	DIAGONAL_LEFT = 8
}	t_direction;

typedef struct s_edge_exploration_context{
	t_vector4d		coord;
	t_vector4d		delta;
	t_vector4d		current_coord;
	t_segment_d		segment;
	char			**map;
	t_direction		direction;
	t_direction		**visited;
}	t_edge_exploration_context;



typedef struct s_bsp_tree_node_data
{
	t_segment_d		separator;
	t_list			*sector_segments;
	t_sector_data	sector_data;
}	t_bsp_tree_node_data;

typedef struct s_cub
{
	t_img_data				texture[4];
	t_img_data				screen;
	t_img_data				ui_images[UI_ASSET_COUNT];
	t_img_data				game_images[GAME_ASSET_COUNT];
	uint32_t				floor;
	uint32_t				celling;
	t_point2i				mouse_pos;
	t_player				player;
	t_dda					dda;
	size_t					mapwidth;
	size_t					mapheight;
	t_img					img;
	void					*mlx_ptr;
	void					*win_ptr;
	char					**map;
	t_drawing_state			drawing;
	t_update_type			update;
	t_modus_state			*game_states;
	t_modus_state			game_state;
	t_list					*canvas_list;
	void					*active_canvas;
	void					*setup_canvas;
	t_list					*segments_list;
	t_inputs				inputs; //TODO: move it
	t_game_data				game_data;
	t_texture_manager		texture_manager;
}				t_cub;

typedef struct s_event_handlers {
	int	(*on_keypress)(int keysym, void *self, t_cub *data);
	int	(*on_keyrelease)(int keysym, void *self, t_cub *data);
	int	(*on_boutonpress)(int keysym, t_point2i mouse_pos,
			void *self, t_cub *data);
	int	(*on_mousemove)(t_point2i mouse_pos, void *self, t_cub *data);
	int	(*render)(void *self, t_cub *data);
}	t_event_handlers;

typedef int				(*t_canvas_func)(void *, t_cub *);

typedef struct s_texture_mapping_data
{
	t_segment_d	*surface;
	t_segment_d	relative_segment;
	t_segment_d	clipped_relative_segment;
	t_img_data	*texture;
	double		texture_width;
	double		texture_tiling_factor_x;
	double		texture_tiling_factor_y;
	double		u0;
	double		u1;
	t_segment_d	projected_top;
	t_segment_d	projected_bot;
	double		coef_top;
	double		coef_bot;
	double		x;
	double		top;
	double		bot;
	double		left;
	double		right;
	t_vector4d	world_pos;
	t_vector4d	normal;
	double		depth;
	int			img_x;
}				t_texture_mapping_data;

typedef struct s_billboard
{
	t_vector4d		pos;
	t_vector4d		dir;
	t_vector4d		right;
	t_vector4d		size;
	t_texture_ptr	texture;
	t_texture_ptr	normal_map;
}	t_billboard;

#endif
