// DarkEdifPreBuildTool: This file was generated for a Extension.cpp/h that was modified at 2024-09-04T21:39:33.9557457Z.
// This file is used by the DarkEdifPreBuildTool as an input template for the calltable generator.
// Do not modify or delete this file.
#if DARKEDIF_ACE_CALL_TABLE_INDEX==0

#elif DARKEDIF_ACE_CALL_TABLE_INDEX==1
			case 1:
				return ext->set_noise_type(*(int *)&Parameters[0]), 0;
			case 24:
				return ext->set_noise_upper_range(*(float *)&Parameters[0]), 0;
			case 25:
				return ext->set_noise_lower_range(*(float *)&Parameters[0]), 0;
			case 0:
				return ext->set_noise_seed(*(int *)&Parameters[0]), 0;
			case 2:
				return ext->set_noise_frequency(*(float *)&Parameters[0]), 0;
			case 12:
				return ext->set_noise_rotation_type_3d(*(int *)&Parameters[0]), 0;
			case 3:
				return ext->set_noise_fractal_type(*(int *)&Parameters[0]), 0;
			case 4:
				return ext->set_noise_fractal_octaves(*(int *)&Parameters[0]), 0;
			case 5:
				return ext->set_noise_fractal_lacunarity(*(float *)&Parameters[0]), 0;
			case 11:
				return ext->set_noise_fractal_gain(*(float *)&Parameters[0]), 0;
			case 6:
				return ext->set_noise_fractal_weighted(*(float *)&Parameters[0]), 0;
			case 7:
				return ext->set_noise_fractal_pingpong(*(float *)&Parameters[0]), 0;
			case 8:
				return ext->set_noise_cellular_distance_function(*(int *)&Parameters[0]), 0;
			case 9:
				return ext->set_noise_cellular_return_type(*(int *)&Parameters[0]), 0;
			case 10:
				return ext->set_noise_cellular_jitter(*(float *)&Parameters[0]), 0;
			case 13:
				return ext->enable_warp(), 0;
			case 14:
				return ext->disable_warp(), 0;
			case 15:
				return ext->set_warp_type(*(int *)&Parameters[0]), 0;
			case 16:
				return ext->set_warp_amp(*(float *)&Parameters[0]), 0;
			case 17:
				return ext->set_warp_seed(*(int *)&Parameters[0]), 0;
			case 18:
				return ext->set_warp_frequency(*(float *)&Parameters[0]), 0;
			case 19:
				return ext->set_warp_rotation_type_3d(*(int *)&Parameters[0]), 0;
			case 20:
				return ext->set_warp_fractal_type(*(int *)&Parameters[0]), 0;
			case 21:
				return ext->set_warp_fractal_octaves(*(int *)&Parameters[0]), 0;
			case 22:
				return ext->set_warp_fractal_lacunarity(*(float *)&Parameters[0]), 0;
			case 23:
				return ext->set_warp_fractal_gain(*(float *)&Parameters[0]), 0;
			case 26:
				return ext->fill_surface_obj_with_noise(*(RunObject* *)&Parameters[0], *(float *)&Parameters[1], *(float *)&Parameters[2], *(float *)&Parameters[3], *(int *)&Parameters[4]), 0;

#elif DARKEDIF_ACE_CALL_TABLE_INDEX==2
		case 2:
			*((float *)&Result) = ext->get_noise3D(*(float *)&Parameters[0], *(float *)&Parameters[1], *(float *)&Parameters[2]);
			break;
		case 3:
			*((float *)&Result) = ext->get_noise2D(*(float *)&Parameters[0], *(float *)&Parameters[1]);
			break;
		case 4:
			*((float *)&Result) = ext->get_noise1D(*(float *)&Parameters[0]);
			break;
		case 5:
			*((float *)&Result) = ext->get_looping_noise1D(*(float *)&Parameters[0], *(float *)&Parameters[1], *(float *)&Parameters[2]);
			break;
		case 1:
			*((int *)&Result) = ext->string_to_seed(*(const TCHAR* *)&Parameters[0]);
			break;
		case 6:
			*((int *)&Result) = ext->always_0();
			break;
		case 7:
			*((int *)&Result) = ext->always_1();
			break;
		case 8:
			*((int *)&Result) = ext->always_2();
			break;
		case 9:
			*((int *)&Result) = ext->always_3();
			break;
		case 10:
			*((int *)&Result) = ext->always_4();
			break;
		case 11:
			*((int *)&Result) = ext->always_5();
			break;
		case 31:
			*((int *)&Result) = ext->always_1();
			break;
		case 32:
			*((int *)&Result) = ext->always_2();
			break;
		case 12:
			*((int *)&Result) = ext->always_0();
			break;
		case 13:
			*((int *)&Result) = ext->always_1();
			break;
		case 14:
			*((int *)&Result) = ext->always_2();
			break;
		case 15:
			*((int *)&Result) = ext->always_3();
			break;
		case 16:
			*((int *)&Result) = ext->always_0();
			break;
		case 17:
			*((int *)&Result) = ext->always_1();
			break;
		case 18:
			*((int *)&Result) = ext->always_2();
			break;
		case 19:
			*((int *)&Result) = ext->always_3();
			break;
		case 20:
			*((int *)&Result) = ext->always_0();
			break;
		case 21:
			*((int *)&Result) = ext->always_1();
			break;
		case 22:
			*((int *)&Result) = ext->always_2();
			break;
		case 23:
			*((int *)&Result) = ext->always_3();
			break;
		case 24:
			*((int *)&Result) = ext->always_4();
			break;
		case 25:
			*((int *)&Result) = ext->always_5();
			break;
		case 26:
			*((int *)&Result) = ext->always_6();
			break;
		case 34:
			*((int *)&Result) = ext->always_1();
			break;
		case 35:
			*((int *)&Result) = ext->always_2();
			break;
		case 36:
			*((int *)&Result) = ext->always_4();
			break;
		case 37:
			*((int *)&Result) = ext->always_5();
			break;
		case 0:
			*((int *)&Result) = ext->current_noise_seed();
			break;
		case 27:
			*((int *)&Result) = ext->current_noise_type();
			break;
		case 33:
			*((int *)&Result) = ext->current_noise_rotation_type_3d();
			break;
		case 28:
			*((int *)&Result) = ext->current_noise_fractal_type();
			break;
		case 29:
			*((int *)&Result) = ext->current_noise_cellular_function();
			break;
		case 30:
			*((int *)&Result) = ext->current_noise_cellular_return_type();
			break;
		case 38:
			*((int *)&Result) = ext->is_warp_enabled();
			break;
		case 39:
			*((int *)&Result) = ext->current_warp_seed();
			break;
		case 40:
			*((int *)&Result) = ext->current_warp_type();
			break;
		case 41:
			*((int *)&Result) = ext->current_warp_rotation_type_3d();
			break;
		case 42:
			*((int *)&Result) = ext->current_warp_fractal_type();
			break;
		case 43:
			*((int *)&Result) = ext->default_flags();
			break;
		case 44:
			*((int *)&Result) = ext->fill_red();
			break;
		case 45:
			*((int *)&Result) = ext->fill_green();
			break;
		case 46:
			*((int *)&Result) = ext->fill_blue();
			break;
		case 47:
			*((int *)&Result) = ext->fill_alpha();
			break;
		case 48:
			*((int *)&Result) = ext->only_2d();
			break;

#else
	#error Incorrect DarkEdif ACE Call Table index
#endif
