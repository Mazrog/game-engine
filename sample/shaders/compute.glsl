#version 430

#extension GL_ARB_compute_shader : enable;
#extension GL_ARB_shader_storage_buffer_object : enable;


layout ( local_size_x = 16, local_size_y = 16, local_size_z = 1 ) in;

