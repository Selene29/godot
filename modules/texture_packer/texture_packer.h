/*
Copyright (c) 2019-2020 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef TEXTURE_PACKER_H
#define TEXTURE_PACKER_H

#include "core/math/color.h"
#include "core/io/image.h"
#include "core/object/reference.h"
#include "core/string/ustring.h"
#include "core/templates/vector.h"
#include "scene/resources/texture.h"
#include <vector>

#include "rectpack2D/pack.h"

#include "core/version.h"

#if VERSION_MAJOR >= 4
#define PoolVector Vector
#define Texture Texture2D
#define PoolByteArray PackedByteArray

#define REAL FLOAT
#endif

class TexturePacker : public Reference {
	GDCLASS(TexturePacker, Reference);

public:
	int get_texture_flags() const;
	void set_texture_flags(const int flags);

	int get_max_atlas_size() const;
	void set_max_atlas_size(const int size);

	bool get_keep_original_atlases() const;
	void set_keep_original_atlases(const bool value);

	Color get_background_color() const;
	void set_background_color(const Color color);

	int get_margin() const;
	void set_margin(const int margin);

	Ref<AtlasTexture> add_texture(Ref<Texture> texture);

	Ref<AtlasTexture> get_texture(Ref<Texture> texture);
	Ref<AtlasTexture> get_texture_index(int index);

	Ref<Texture> get_original_texture(int index);

	bool contains_texture(Ref<Texture> texture);

	bool unref_texture_index(int index);
	bool unref_texture(Ref<Texture> texture);
	void remove_texture_index(int index);
	void remove_texture(Ref<Texture> texture);

	int get_texture_count();
	void clear();

	Ref<ImageTexture> get_generated_texture(int index);
	int get_generated_texture_count();

	void merge();

	int get_offset_for_format(Image::Format format);

	TexturePacker();
	~TexturePacker();

protected:
	static void _bind_methods();

private:
	int _texture_flags;
	int _max_atlas_size;
	bool _keep_original_atlases;
	Color _background_color;
	int _margin;

	Vector<rect_xywhf *> _rects;
	Vector<Ref<ImageTexture> > _generated_textures;
};

#endif
