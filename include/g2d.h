#ifndef G2D_H_
#define G2D_H_

#include "basic.hpp"
#include <functional>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace g2d {
    static Point mouse_pos_{0, 0};
    static Point size_{640, 480};
    static std::set<std::string> current_keys_;
    static std::set<std::string> previous_keys_;
    static std::function<void()> usr_tick_;
    static int fps_ = 30;
    static char key_buffer_[128];

    static std::stringstream cout;
    static const int cout_size_ = 64 * 1024;
    static char cout_buffer_[cout_size_];
    static auto o0_ = [] { cout << 0; cout.str(""); return 0; } ();

    extern "C" void js_init_canvas(double w, double h){return ;};
    extern "C" void js_close_canvas();
    extern "C" void js_set_color(double r, double g, double b);
    extern "C" void js_set_timeout(double fps);
    extern "C" double js_width();
    extern "C" double js_height();
    extern "C" void js_clear_rect(double x, double y, double width, double height);
    extern "C" void js_fill_rect(double x, double y, double width, double height);
    extern "C" void js_fill_circle(double x, double y, double r);
    extern "C" void js_load_element(const char * tag, const char * src);
    extern "C" void js_draw_image(const char * src, double x, double y);
    extern "C" void js_draw_image_clip(const char * src, double x, double y, double x0, double y0, double w, double h);
    extern "C" void js_draw_text(const char * txt, double x, double y, double size, char * baseline, char * align);
    extern "C" void js_play_audio(const char * src, double loop);
    extern "C" void js_pause_audio(const char * src);
    extern "C" void js_alert(const char * txt);
    extern "C" bool js_confirm(const char * txt);
    extern "C" void js_prompt(const char * txt, char * ans, int len);

    extern "C" const char * cpp_cout() {
        strncpy(cout_buffer_, cout.str().c_str(), cout_size_-1);
        cout_buffer_[cout_size_] = 0;
        return cout_buffer_;

        auto str = cout.str();
        auto txt = str.substr(0, cout_size_-1);
        if (txt.back() & 0x80 == 0x80) {
            while (txt.back() & 0xC0 == 0x80) txt.pop_back();
            txt.pop_back();
        }
        strncpy(cout_buffer_, txt.c_str(), txt.size()+1);
        cout.str(str.erase(0, txt.size()));
        return cout_buffer_;
    }
    extern "C" char * cpp_key_buffer() {
        return key_buffer_;
    }
    extern "C" void cpp_keydown() {
        current_keys_.insert(key_buffer_);
    }
    extern "C" void cpp_keyup() {
        current_keys_.erase(key_buffer_);
    }
    extern "C" void cpp_mousemove(double x, double y) {
        mouse_pos_ = {x, y};
    }
    extern "C" void cpp_tick() {
        if (usr_tick_ != nullptr) {
            usr_tick_();
        }
        previous_keys_ = current_keys_;
    }

    void init_canvas(Point p) { size_ = p; js_init_canvas(p.x, p.y); }
    void close_canvas() { js_close_canvas(); }
    void clear_canvas() { js_clear_rect(0, 0, size_.x, size_.y); }
    void set_color(Color c) { js_set_color(c.r, c.g, c.b); }
    void update_canvas() { }
    Point canvas_size() { return size_; }
    void fill_rect(Point p, Point s) { js_fill_rect(p.x, p.y, s.x, s.y); }
    void fill_circle(Point p, int r) { js_fill_circle(p.x, p.y, r); }
    std::string load_image(std::string src) { js_load_element("IMG", src.c_str()); return src; }
    void draw_image(std::string src, Point p) { js_draw_image(src.c_str(), p.x, p.y); }
    void draw_image_clip(std::string src, Point p, Point p0, Point s) { js_draw_image_clip(src.c_str(), p.x, p.y, p0.x, p0.y, s.x, s.y); }
    void draw_text(std::string txt, Point p, int size) { js_draw_text(txt.c_str(), p.x, p.y, size, "top", "left"); }
    void draw_text_centered(std::string txt, Point p, int size) { js_draw_text(txt.c_str(), p.x, p.y, size, "middle", "center"); }
    std::string load_audio(std::string src) { js_load_element("AUDIO", src.c_str()); return src; }
    void play_audio(std::string src, bool loop=false) { js_play_audio(src.c_str(), int(loop)); }
    void pause_audio(std::string src) { js_pause_audio(src.c_str()); }

    void alert(std::string msg) { js_alert(msg.c_str()); }
    bool confirm(std::string msg) { return js_confirm(msg.c_str()); }
    std::string prompt(std::string msg) { char ans[100]; js_prompt(msg.c_str(), ans, 100); return {ans}; }

    Point mouse_pos() { return mouse_pos_; }
    bool mouse_clicked() {
        std::string key = "LeftButton";
        return previous_keys_.count(key) && ! current_keys_.count(key);
    }
    bool key_pressed(std::string key) {
        return current_keys_.count(key) && ! previous_keys_.count(key);
    }
    bool key_released(std::string key) {
        return previous_keys_.count(key) && ! current_keys_.count(key);
    }
    std::set<std::string> current_keys() { return current_keys_; }
    std::set<std::string> previous_keys() { return previous_keys_; }

    void main_loop() { }
    void main_loop(void (*tick)(), int fps=30) {
        fps_ = fps;
        usr_tick_ = std::function<void()>(tick);
        js_set_timeout(fps);
    }
    void main_loop(std::function<void()> tick, int fps=30) {
        fps_ = fps;
        usr_tick_ = tick;
        js_set_timeout(fps);
    }

}

#endif // G2DCANVAS_HPP