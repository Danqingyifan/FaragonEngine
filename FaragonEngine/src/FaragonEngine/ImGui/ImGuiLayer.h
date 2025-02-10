#pragma once
#include "FaragonEngine/Layer.h"
namespace FaragonEngine
{
    class FARAGON_API ImGuiLayer : public Layer
    {
    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach() override;
        void OnDetach() override;
        void OnUpdate() override;
        void OnEvent(Event &event) override;

    private:
    };
}
