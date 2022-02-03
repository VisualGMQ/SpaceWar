_Pragma("once")

#include "pch.hpp"
#include "texture.hpp"
#include "tool.hpp"
#include "renderer.hpp"

/*
 * @brief a small tool to draw simple chars without font resource.
 *        supported chars: 0~9, a~z, `:`,
 * @warning use this when you don't want contact your application with ttf font resource, like unit test.
 *          don't use this in your game, this works slowly and ugly!
 */
class InnerBmpFont final {
public:
    InnerBmpFont();
    InnerBmpFont(const InnerBmpFont& o) = delete;
    InnerBmpFont& operator=(const InnerBmpFont& o) = delete;

    void RenderChar(int ch, int pt, const Point& pos, const Color& color);
    void Render(const std::string& str,
                int pt,
                const Point& pos,
                const Color& color);
    bool HasChar(int ch);

private:
    static constexpr int FontWidth = 8;
    static constexpr int FontHeight = 8;
    using fontMat = std::array<bool, FontWidth * FontHeight>;
    fontMat errorChar_;
    std::unordered_map<char, fontMat> chars_;
    Unique<Texture> errorTexture_ = nullptr;

    void saveChar(char c, const fontMat& m);
    void renderChar(const fontMat& data,
                    int pt,
                    const Point& pos,
                    const Color& color);
};
