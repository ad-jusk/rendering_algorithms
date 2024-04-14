#pragma once

#include "shader/Shader.hpp"

class SimpleShader : public Shader {

    public:
        void preProcess() override;
        void vertexShader(Triangle& triangle) const override;
        void setModel(const Matrix4& newModel) { model = newModel; preProcess(); }
        void setView(const Matrix4& newView) { view = newView; preProcess(); }
        void setProjection(const Matrix4& newProjection) { projection = newProjection; preProcess(); }

        void setAmbientLight(const AmbientLight& ambientLight) { this->ambientLight = ambientLight; }
        void setDirectionalLight(const DirectionalLight& directionalLight) { this->directionalLight = directionalLight; }
        void addPointLight(const PointLight& pointLight) { pointLights.push_back(pointLight); }
};