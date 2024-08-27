#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <vector>
using namespace std;


class Mesh
{
public:
	Mesh() {;}

	Mesh(vector<Vertex> ver, vector<GLuint> ind, GLuint tex, vector<VertexBones> bone,const char* texture_file) {
		vertices.assign(ver.begin(), ver.end());
		indices.assign(ind.begin(), ind.end());
		texture = tex;
		bones_id_weight.assign(bone.begin(), bone.end());

		setup(texture_file);
	}

	void draw(GLuint program)
	{
		// // Bind appropriate textures
        // int diffuse = 1;
        // int specular = 1;

		// glActiveTexture(GL_TEXTURE0); // Active proper texture unit before binding
		// // Retrieve texture number (the N in diffuse_textureN)
		// stringstream ss;
		// string number;
		// string name = this->textures[i].type;
		
		// if( name == "texture_diffuse" )
		// {
		// 	ss << diffuseNr++; // Transfer GLuint to stream
		// }
		// else if( name == "texture_specular" )
		// {
		// 	ss << specularNr++; // Transfer GLuint to stream
		// }
		
		// number = ss.str( );
		// Now set the sampler to the correct texture unit
		// glUniform1i( glGetUniformLocation( shader.Program, ( name + number ).c_str( ) ), i );
		// And finally bind the texture
		//glBindTexture( GL_TEXTURE_2D, this->textures[i].id );
        
        // Also set each mesh's shininess property to a default value (if you want you could extend this to another mesh property and possibly change this value)
        // glUniform1f( glGetUniformLocation( shader.Program, "material.shininess" ), 16.0f );
        
        // Draw mesh
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,(int) indices.size( ), GL_UNSIGNED_INT, 0 );

        glBindVertexArray(0);
	}

	void release()
	{
		glDeleteVertexArrays(1, &vao);
		glDeleteTextures(1, &texture);
		glDeleteBuffers(1, &vbo_vertices);
		glDeleteBuffers(1, &vbo_bones);
		glDeleteBuffers(1, &ebo);	
	}

	// mini bmp loader written by HSU YOU-LUN
	static unsigned char *load_bmp(const char *bmp, unsigned int *width, unsigned int *height, unsigned short int *bits)
	{
		unsigned char *result = nullptr;
		FILE *fp = fopen(bmp, "rb");
		if (!fp)
			return nullptr;
		char type[2];
		unsigned int size, offset;
		// check for magic signature	
		fread(type, sizeof(type), 1, fp);
		if (type[0] == 0x42 || type[1] == 0x4d) {
			fread(&size, sizeof(size), 1, fp);
			// ignore 2 two-byte reversed fields
			fseek(fp, 4, SEEK_CUR);
			fread(&offset, sizeof(offset), 1, fp);
			// ignore size of bmpinfoheader field
			fseek(fp, 4, SEEK_CUR);
			fread(width, sizeof(*width), 1, fp);
			fread(height, sizeof(*height), 1, fp);
			// ignore planes field
			fseek(fp, 2, SEEK_CUR);
			fread(bits, sizeof(*bits), 1, fp);
			unsigned char *pos = result = new unsigned char[size - offset];
			fseek(fp, offset, SEEK_SET);
			while (size - ftell(fp)>0)
				pos += fread(pos, 1, size - ftell(fp), fp);
		}
		fclose(fp);
		return result;
	}

private:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	GLuint texture;
	vector<VertexBones> bones_id_weight;

	GLuint vao;
	GLuint vbo_vertices;
	GLuint vbo_bones;
	GLuint ebo;

	void setup(const char* texbmp) {
		// VAO
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Verteices
		glGenBuffers(1, &vbo_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
			// Upload postion array
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) 0);
        	// Vertex Normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, normal));
        	// Vertex Texture Coords
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*) offsetof(Vertex, texCoords));
        
		// Bones
		glGenBuffers(1, &vbo_bones);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_bones);
		glBufferData(GL_ARRAY_BUFFER, bones_id_weight.size() * sizeof(bones_id_weight[0]), &bones_id_weight[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(3);
		glVertexAttribIPointer(3, MAX_BONES_PER_VERTEX, GL_INT, sizeof(VertexBones), (GLvoid*) 0);
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, MAX_BONES_PER_VERTEX, GL_FLOAT, GL_FALSE, sizeof(VertexBones), (GLvoid*) offsetof(VertexBones, weights));

		// Indices
		glGenBuffers(1, &ebo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);

		// glGenTextures(1, &texture);

		// glBindTexture(GL_TEXTURE_2D, texture);
		// unsigned int width, height;
		// unsigned short int bits;
		// unsigned char *bgr = load_bmp(texbmp, &width, &height, &bits);
		// GLenum format = (bits == 24 ? GL_BGR : GL_BGRA);
		// glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, bgr);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		// glGenerateMipmap(GL_TEXTURE_2D);
		// delete[] bgr;
	}
};