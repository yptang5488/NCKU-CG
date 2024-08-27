#define GLM_ENABLE_EXPERIMENTAL
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

#define MAX_BONES 240
#define MAX_BONES_PER_VERTEX 4

glm::quat rotate_init = glm::quat(cos(glm::radians(0.0f)), sin(glm::radians(0.0f)) * glm::vec3(1.0f, 0.0f, 0.0f));

struct Vertex{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

struct BoneMatrix{
	glm::mat4x4 offset;
	glm::mat4x4 final_transform;
};

struct VertexBones{
	GLuint ids[MAX_BONES_PER_VERTEX]; // max bones influced per vertex
	float weights[MAX_BONES_PER_VERTEX];

	VertexBones(){
		memset(ids, 0, sizeof(ids));
		memset(weights, 0, sizeof(weights));
	}

	void addBoneData(GLuint id, float weight){
		for (int i = 0; i < MAX_BONES_PER_VERTEX; i++) {
			if (weights[i] == 0) {
				ids[i] = id;
				weights[i] = weight;
				return;
			}
		}
	}
};

class Mesh{
public:
	Mesh() {;}

	Mesh(vector<Vertex> ver, vector<GLuint> ind, vector<VertexBones> bone) {
		vertices.assign(ver.begin(), ver.end());
		indices.assign(ind.begin(), ind.end());
		bones_id_weight.assign(bone.begin(), bone.end());

		setup();
	}

	void draw(GLuint program){   
        // Draw mesh
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES,(int) indices.size( ), GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
	}

	void release()
	{
		glDeleteVertexArrays(1, &vao);
		// glDeleteTextures(1, &texture);
		glDeleteBuffers(1, &vbo_vertices);
		glDeleteBuffers(1, &vbo_bones);
		glDeleteBuffers(1, &ebo);	
	}

private:
	vector<Vertex> vertices;
	vector<GLuint> indices;
	// GLuint texture;
	vector<VertexBones> bones_id_weight;

	GLuint vao;
	GLuint vbo_vertices;
	GLuint vbo_bones;
	GLuint ebo;

	void setup() {
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
	}
};

class Model{
public:
    Model(){;}

	/* load model */
    Model(const string path){
        scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
			std::cout << "error assimp : " << importer.GetErrorString() << std::endl;
			return;
		}

        const aiMatrix4x4 m = scene->mRootNode->mTransformation.Inverse();
        inverse_transform = glm::transpose(glm::make_mat4(&m.a1));

		cout << "scene->HasAnimations(): " << scene->HasAnimations() << endl;
		if (scene->HasAnimations()) {
			if (scene->mAnimations[0]->mTicksPerSecond != 0.0) {
				ticks_per_second = scene->mAnimations[0]->mTicksPerSecond;
			} else {
				ticks_per_second = 25.0f;
			}
			cout << "scene->mAnimations[0]->mNumChannels: " << scene->mAnimations[0]->mNumChannels << endl;
			cout << "scene->mAnimations[0]->mDuration: " << scene->mAnimations[0]->mDuration << endl;
			cout << "scene->mAnimations[0]->mTicksPerSecond: " << scene->mAnimations[0]->mTicksPerSecond << endl << endl;
			cout << "name nodes animation : " << endl;
			for (uint i = 0; i < scene->mAnimations[0]->mNumChannels; i++) {
				cout<< scene->mAnimations[0]->mChannels[i]->mNodeName.C_Str() << endl;
			}
		}
		cout << endl;
		
		cout << "nodes:" << endl;
		showNode(scene->mRootNode);
		cout << endl;

		processMesh(scene);
    }

	/* set bone_location[] : for assigning the uniform variable later */
	void initBoneLoc(GLuint program){
		for (int i = 0; i < MAX_BONES; i++) {
			string name = "bones[" + to_string(i) + "]";
			bone_location[i] = glGetUniformLocation(program, name.c_str()); //Returns the location of a uniform variable
		}
	}

    void showNode(aiNode* node){
		std::cout << node->mName.data << std::endl;
		for (int i = 0; i < node->mNumChildren; i++){
			showNode(node->mChildren[i]);
		}
	}

	/* render the model */
	void render(GLuint program, bool run_animation){
		float ticks = (float)glfwGetTime() * ticks_per_second;
		float animation_time = 0;
		if (scene->HasAnimations()) animation_time = fmod(ticks, scene->mAnimations[0]->mDuration);

		glm::mat4 identity_matrix(1.0f);
		if (run_animation) {
			readNodeHierarchy(animation_time, scene->mRootNode, identity_matrix, run_animation);
		} else {
			readNodeHierarchy(0, scene->mRootNode, identity_matrix, run_animation);
		}
		
		/* set bone_loction (uniform variable) value */
		vector<glm::mat4x4> transforms;
		transforms.resize(num_bones);
		for (int i = 0; i < num_bones; i++) {
			transforms[i] = bone_matrices[i].final_transform;
		}
		
		for (int i = 0; i < transforms.size(); i++) {
			glUniformMatrix4fv(bone_location[i], 1, GL_FALSE, glm::value_ptr(transforms[i]));
		}
		
		/* draw for each mesh */
		for (int i = 0; i < meshes.size(); i++) {
            meshes[i].draw(program);
        }
	}

	void update(bool keys_pressed[]){
		// head
		if (keys_pressed[GLFW_KEY_1])
			rotate_head *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(-1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_2])
        	rotate_head *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(-1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_3])
			rotate_head *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_4])
			rotate_head *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		
		// body
		if (keys_pressed[GLFW_KEY_5])
			rotate_body *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(-1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_6])
        	rotate_body *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(-1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_7])
			rotate_body *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_8])
			rotate_body *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		
		// front left leg2
		if (keys_pressed[GLFW_KEY_R])
			rotate_fl_leg2 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_F])
			rotate_fl_leg2 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		// front left leg1
		if (keys_pressed[GLFW_KEY_T])
        	rotate_fl_leg1 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_G])
			rotate_fl_leg1 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		// front right leg1
		if (keys_pressed[GLFW_KEY_Y])
        	rotate_fr_leg1 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, -1.0f));
		if (keys_pressed[GLFW_KEY_H])
			rotate_fr_leg1 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, -1.0f));
		// front right leg2
		if (keys_pressed[GLFW_KEY_U])
        	rotate_fr_leg2 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, -1.0f));
		if (keys_pressed[GLFW_KEY_J])
			rotate_fr_leg2 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, -1.0f));
		
		// back left leg2
		if (keys_pressed[GLFW_KEY_I])
			rotate_bl_leg2 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_K])
			rotate_bl_leg2 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		// back left leg1
		if (keys_pressed[GLFW_KEY_O])
        	rotate_bl_leg1 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_L])
			rotate_bl_leg1 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		// back right leg1
		if (keys_pressed[GLFW_KEY_P])
        	rotate_br_leg1 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_SEMICOLON])
			rotate_br_leg1 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		// back right leg2
		if (keys_pressed[GLFW_KEY_LEFT_BRACKET])
        	rotate_br_leg2 *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_APOSTROPHE])
			rotate_br_leg2 *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, 1.0f));
		
		// tail
		if (keys_pressed[GLFW_KEY_Z])
			rotate_tail *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(1.0f, 0.0f, -1.0f));
		if (keys_pressed[GLFW_KEY_X])
        	rotate_tail *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(1.0f, 0.0f, -1.0f));
		if (keys_pressed[GLFW_KEY_C])
			rotate_tail *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(-1.0f, 0.0f, -1.0f));
		if (keys_pressed[GLFW_KEY_V])
			rotate_tail *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(-1.0f, 0.0f, -1.0f));

		//left wing
		if (keys_pressed[GLFW_KEY_B])
			rotate_left_wing *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(0.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_N])
        	rotate_left_wing *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(0.0f, 0.0f, 1.0f));
		//right wing
		if (keys_pressed[GLFW_KEY_M])
			rotate_right_wing *= glm::quat(cos(glm::radians(1.0f / 2)), sin(glm::radians(-1.0f / 2)) * glm::vec3(0.0f, 0.0f, 1.0f));
		if (keys_pressed[GLFW_KEY_COMMA])
        	rotate_right_wing *= glm::quat(cos(glm::radians(-1.0f / 2)), sin(glm::radians(1.0f / 2)) * glm::vec3(0.0f, 0.0f, 1.0f));
	}

private:
    Assimp::Importer importer;
    const aiScene* scene;
    glm::mat4x4 inverse_transform;
    float ticks_per_second = 0;

    map<string, GLuint> bone_mapping; //bone name -> index
    GLuint num_bones = 0;
	vector<BoneMatrix> bone_matrices;
	GLuint bone_location[MAX_BONES]; //location of a uniform variable

    vector<Mesh> meshes;

	glm::quat rotate_head = rotate_init;
	glm::quat rotate_body = rotate_init;
	glm::quat rotate_fl_leg1 = rotate_init;
	glm::quat rotate_fl_leg2 = rotate_init;
	glm::quat rotate_fr_leg1 = rotate_init;
	glm::quat rotate_fr_leg2 = rotate_init;
	glm::quat rotate_bl_leg1 = rotate_init;
	glm::quat rotate_bl_leg2 = rotate_init;
	glm::quat rotate_br_leg1 = rotate_init;
	glm::quat rotate_br_leg2 = rotate_init;
	glm::quat rotate_tail = rotate_init;
	glm::quat rotate_left_wing = rotate_init;
	glm::quat rotate_right_wing = rotate_init;


    void processMesh(const aiScene* scene){
		Mesh mesh;
        // cout << "scene->mNemMeshes:" << scene->mNumMeshes << endl;
		for (int i = 0; i < scene->mNumMeshes; i++) { // 2 : "Armature_Bone_root", "Sphere_001"
			aiMesh* ai_mesh = scene->mMeshes[i];

			vector<Vertex> vertices;
			vector<GLuint> indices;
			vector<VertexBones> bones_id_weight;
			// GLuint texture;

			vertices.reserve(ai_mesh->mNumVertices);
			indices.reserve(ai_mesh->mNumVertices);
			bones_id_weight.resize(ai_mesh->mNumVertices);

            /* vertices */
            // cout << "ai_mesh->mNumVertices:" << ai_mesh->mNumVertices << endl;
			for (int i = 0; i < ai_mesh->mNumVertices; i++) {
				Vertex vertex;
				glm::vec3 vector;

                vector = {ai_mesh->mVertices[i].x, ai_mesh->mVertices[i].y, ai_mesh->mVertices[i].z};
                vertex.position = vector;

				vector.x = ai_mesh->mNormals[i].x;
				vector.y = ai_mesh->mNormals[i].y;
				vector.z = ai_mesh->mNormals[i].z;
				vertex.normal = vector;

				if(ai_mesh->mTextureCoords[0]) {
					glm::vec2 vec;
                    vec = {ai_mesh->mTextureCoords[0][i].x, ai_mesh->mTextureCoords[0][i].y};
					// vec.x = ai_mesh->mTextureCoords[0][i].x;
					// vec.y = ai_mesh->mTextureCoords[0][i].y;
					vertex.texCoords = vec;
				} else {
					vertex.texCoords = glm::vec2(0.0f, 0.0f);
				}
				vertices.push_back(vertex);
			}

            /* indices of faces */
			for (int i = 0; i < ai_mesh->mNumFaces; i++) {
				aiFace face = ai_mesh->mFaces[i];
				for(unsigned int j = 0; j < face.mNumIndices; j++)
            		indices.push_back(face.mIndices[j]);
			}

            /* bones */
			for (int i = 0; i < ai_mesh->mNumBones; i++) {
				int bone_index = 0;
				string bone_name = ai_mesh->mBones[i]->mName.data;

				if (bone_mapping.find(bone_name) == bone_mapping.end()) { //find a new bone
					bone_index = num_bones;
					num_bones++;

					BoneMatrix bone_matrix;
                    const aiMatrix4x4 m = ai_mesh->mBones[i]->mOffsetMatrix;
                    bone_matrix.offset = glm::transpose(glm::make_mat4(&m.a1));
					bone_matrices.push_back(bone_matrix);
					bone_mapping[bone_name] = bone_index;
                    // if(i < 20){
                    //     cout << "bone_name: " << bone_name << endl;
                    //     cout << "bone_index: " << bone_index << endl;
                    // }
					
				} else {
					bone_index = bone_mapping[bone_name];
                    // cout << "found bone name:"<< bone_name << ",bone_index = " << bone_index << endl;
				}

                // cout << ai_mesh->mBones[i]->mNumWeights << endl;
				for (int j = 0; j < ai_mesh->mBones[i]->mNumWeights; j++) {
					GLuint vertex_id = ai_mesh->mBones[i]->mWeights[j].mVertexId;
					float weight = ai_mesh->mBones[i]->mWeights[j].mWeight;
					bones_id_weight[vertex_id].addBoneData(bone_index, weight);

                    // if(j == 0){
                    //     cout << "vertex_id: " << vertex_id << endl;
					//     cout << "bone_index: " << bone_index << endl;
					//     cout << "weight: " << weight << endl;
                    // }
					
				}
			}
			mesh = Mesh(vertices, indices, bones_id_weight);
			meshes.push_back(mesh);
		}
	}

	glm::mat4x4 updateTransfrom(glm::mat4x4 target_trans, glm::quat rotate_source){
		aiQuaternion rotate_h = aiQuaternion(rotate_source.w, rotate_source.x, rotate_source.y, rotate_source.z);
		target_trans *= glm::toMat4(glm::quat(rotate_h.w, rotate_h.x, rotate_h.y, rotate_h.z));
		return target_trans;
	}

	const aiNodeAnim* findNodeAnim(const aiAnimation* animation, const string node_name){
		for (int i = 0; i < animation->mNumChannels; i++) {
			const aiNodeAnim* node_anim = animation->mChannels[i];
			if (string(node_anim->mNodeName.data) == string(node_name)) {
				return node_anim;
			}
		}
		return nullptr;
	}

	int findScaling(float animationTime, const aiNodeAnim* pNodeAnim) {
        assert(pNodeAnim->mNumScalingKeys > 0);
        
        for (unsigned int i = 0; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
            if (animationTime < (float)pNodeAnim->mScalingKeys[i+1].mTime)  return i;
        }
        return -1;
    }

	int findTranslation(float animationTime, const aiNodeAnim* pNodeAnim) {
        assert(pNodeAnim->mNumPositionKeys > 0);
        
        for (unsigned int i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
            if (animationTime < (float)pNodeAnim->mPositionKeys[i+1].mTime)  return i;
        }
        return -1;
    }

	int findRotation(float animationTime, const aiNodeAnim* pNodeAnim) {
        assert(pNodeAnim->mNumRotationKeys > 0);
        
        for (unsigned int i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
            if (animationTime < (float)pNodeAnim->mRotationKeys[i+1].mTime) return i;
        }
        return -1;
    }

	aiVector3D calcInterpolatedScaling(float animation_time, const aiNodeAnim* node_anim){
		if (node_anim->mNumScalingKeys == 1) {
			return node_anim->mScalingKeys[0].mValue;
		}

		int scaling_index = findScaling(animation_time, node_anim);

		int next_scaling_index = scaling_index + 1;
		assert(next_scaling_index < node_anim->mNumScalingKeys);
		float delta_time = node_anim->mScalingKeys[next_scaling_index].mTime - node_anim->mScalingKeys[scaling_index].mTime;
		float factor = (animation_time - node_anim->mScalingKeys[scaling_index].mTime) / delta_time;
		//assert(factor >= 0.0f && factor <= 1.0f);

		aiVector3D start = node_anim->mScalingKeys[scaling_index].mValue;
		aiVector3D end = node_anim->mScalingKeys[next_scaling_index].mValue;
		aiVector3D delta = end - start;

		return start + delta * factor;
	}

	aiVector3D calcInterpolatedPosition(float animation_time, const aiNodeAnim* node_anim){
		if (node_anim->mNumPositionKeys == 1) {
			return node_anim->mPositionKeys[0].mValue;
		}

		int position_index = findTranslation(animation_time, node_anim);
		int next_position_index = position_index + 1;
		assert(next_position_index < node_anim->mNumPositionKeys);
		float delta_time = (float)(node_anim->mPositionKeys[next_position_index].mTime - node_anim->mPositionKeys[position_index].mTime);
		float factor = (animation_time - (float)node_anim->mPositionKeys[position_index].mTime) / delta_time;
		//assert(factor >= 0.0f && factor <= 1.0f);

		aiVector3D start = node_anim->mPositionKeys[position_index].mValue;
		aiVector3D end = node_anim->mPositionKeys[next_position_index].mValue;
		aiVector3D delta = end - start;

		return start + factor * delta;
	}

	void calcInterpolatedRotation(aiQuaternion& quat, float animation_time, const aiNodeAnim* node_anim){
		if (node_anim->mNumRotationKeys == 1) {
			quat = node_anim->mRotationKeys[0].mValue;
			return;
		}
		
		int rotation_index = findRotation(animation_time, node_anim);
		int next_rotation_index = rotation_index + 1;
		assert(next_rotation_index < node_anim->mNumRotationKeys);
		float delta_time = (float)(node_anim->mRotationKeys[next_rotation_index].mTime - node_anim->mRotationKeys[rotation_index].mTime);
		float factor = (animation_time - (float)node_anim->mRotationKeys[rotation_index].mTime) / delta_time;
		//assert(factor >= 0.0f && factor <= 1.0f);

		aiQuaternion start_quat = node_anim->mRotationKeys[rotation_index].mValue;
		aiQuaternion end_quat = node_anim->mRotationKeys[next_rotation_index].mValue;

		aiQuaternion::Interpolate(quat, start_quat, end_quat, factor);
	}

	/* set final transform of each bone */
	void readNodeHierarchy(float animation_time, const aiNode* node, const glm::mat4x4& transform, bool run_animation){
		string node_name = node->mName.data;

		const aiMatrix4x4 m = node->mTransformation;
        glm::mat4x4 node_transform = glm::transpose(glm::make_mat4(&m.a1));

		if (scene->HasAnimations() && run_animation) {
			const aiAnimation* animation = scene->mAnimations[0];
			const aiNodeAnim* node_anim = findNodeAnim(animation, node_name);
			
			if (node_anim) {
				// scaling
				aiVector3D scaling_vector = calcInterpolatedScaling(animation_time, node_anim);
				glm::mat4x4 scaling_matr = glm::mat4x4(1.0f);
				scaling_matr = glm::scale(scaling_matr, glm::vec3(scaling_vector.x, scaling_vector.y, scaling_vector.z));
				
				// rotation
				aiQuaternion rotate_quat;
				calcInterpolatedRotation(rotate_quat, animation_time, node_anim);
				glm::mat4x4 rotate_matr = glm::toMat4(glm::quat(rotate_quat.w, rotate_quat.x, rotate_quat.y, rotate_quat.z));

				// translation
				aiVector3D translate_vector = calcInterpolatedPosition(animation_time, node_anim);
				glm::mat4x4 translate_matr = glm::mat4x4(1.0f);
				translate_matr = glm::translate(translate_matr, glm::vec3(translate_vector.x, translate_vector.y, translate_vector.z));
				
				node_transform = translate_matr * rotate_matr * scaling_matr;
			}
		}

		glm::mat4x4 global_transform = transform * node_transform;

		if (bone_mapping.find(node_name) != bone_mapping.end()) {
			if (node_name == "Armature_Bone_head") 					global_transform = updateTransfrom(global_transform, rotate_head);
			else if (node_name == "Armature_Bone_body") 			global_transform = updateTransfrom(global_transform, rotate_body);
			else if (node_name == "Armature_Bone_front_left_leg1") 	global_transform = updateTransfrom(global_transform, rotate_fl_leg1);
			else if (node_name == "Armature_Bone_front_left_leg2")  global_transform = updateTransfrom(global_transform, rotate_fl_leg2);
			else if (node_name == "Armature_Bone_front_right_leg1") global_transform = updateTransfrom(global_transform, rotate_fr_leg1);
			else if (node_name == "Armature_Bone_front_right_leg2") global_transform = updateTransfrom(global_transform, rotate_fr_leg2);
			else if (node_name == "Armature_Bone_back_left_leg1") 	global_transform = updateTransfrom(global_transform, rotate_bl_leg1);
			else if (node_name == "Armature_Bone_back_left_leg2") 	global_transform = updateTransfrom(global_transform, rotate_bl_leg1);
			else if (node_name == "Armature_Bone_back_right_leg1") 	global_transform = updateTransfrom(global_transform, rotate_br_leg1);
			else if (node_name == "Armature_Bone_back_right_leg2") 	global_transform = updateTransfrom(global_transform, rotate_br_leg1);
			else if (node_name == "Armature_Bone_tail") 			global_transform = updateTransfrom(global_transform, rotate_tail);
			else if (node_name == "Armature_Bone_left_wing") 		global_transform = updateTransfrom(global_transform, rotate_left_wing);
			else if (node_name == "Armature_Bone_right_wing") 		global_transform = updateTransfrom(global_transform, rotate_right_wing);

			int bone_index = bone_mapping[node_name];
			bone_matrices[bone_index].final_transform = inverse_transform * global_transform * bone_matrices[bone_index].offset;
		}

		for (int i = 0; i < node->mNumChildren; i++) {
			readNodeHierarchy(animation_time, node->mChildren[i], global_transform, run_animation);
		}
	}
};