#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<ofColor> base_color_list;
	ofColor color;
	vector<int> hex_list = { 0xef476f, 0xffd166, 0x06d6a0, 0x118ab2, 0x073b4c };
	for (auto hex : hex_list) {

		color.setHex(hex);
		base_color_list.push_back(color);
	}
	int color_index = 0;

	this->cam.begin();

	for (int radius = 30; radius <= 300; radius += 10) {

		ofMesh mesh, frame;
		frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		auto deg_max = ofMap(ofNoise(radius * 0.005 + ofGetFrameNum() * 0.015), 0, 1, 0, 450);
		if (deg_max > 360) { deg_max = 360; }

		for (int deg = 0; deg < deg_max; deg += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));


			mesh.addVertex(glm::vec3(location, -30));
			mesh.addVertex(glm::vec3(location, 30));

			frame.addVertex(glm::vec3(location, -30));
			frame.addVertex(glm::vec3(location, 30));

			if (deg > 0) {

				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 2); mesh.addIndex(mesh.getNumVertices() - 4);
				mesh.addIndex(mesh.getNumVertices() - 1); mesh.addIndex(mesh.getNumVertices() - 3); mesh.addIndex(mesh.getNumVertices() - 4);

				frame.addIndex(frame.getNumVertices() - 1); frame.addIndex(frame.getNumVertices() - 3);
				frame.addIndex(frame.getNumVertices() - 2); frame.addIndex(frame.getNumVertices() - 4);
			}

			mesh.addColor(base_color_list[color_index]);
			mesh.addColor(base_color_list[color_index]);

			frame.addColor(ofColor(39));
			frame.addColor(ofColor(39));
		}

		frame.addIndex(0); frame.addIndex(1);
		frame.addIndex(frame.getNumVertices() - 1);	frame.addIndex(frame.getNumVertices() - 2);

		mesh.draw();
		frame.drawWireframe();

		color_index = (color_index + 1) % base_color_list.size();
	}



	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}