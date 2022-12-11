#pragma once

#include "Button.h"

class SaveButton : public Button
{
public:

    SaveButton(Vector2d shape, Vector2d center, const Texture &texture = Texture(Color::White)) : Button(shape, center, texture),
        file_path_("")
    {
        left_click_command_    = (Command<const Event &> *) new SimpleCommand<SaveButton, const Event &>(this, &SaveButton::SaveClickLeftEvent);
        left_release_command_  = (Command<const Event &> *) new SimpleCommand<SaveButton, const Event &>(this, &SaveButton::SaveReleasedLeftEvent);
        right_click_command_   = (Command<const Event &> *) new SimpleCommand<SaveButton, const Event &>(this, &SaveButton::SaveClickRightEvent);
        right_release_command_ = (Command<const Event &> *) new SimpleCommand<SaveButton, const Event &>(this, &SaveButton::SaveReleasedLeftEvent);
    }

    void set_left_click           (Command<std::string> *command)
    {
        save_left_click_command_    = command;
    }
    void set_release_left_click   (Command<std::string> *command)
    {
        save_left_release_command_  = command;
    }
    void set_right_click          (Command<std::string> *command)
    {
        save_right_click_command_   = command;
    }
    void set_release_right_click  (Command<std::string> *command)
    {
        save_right_release_command_ = command;
    }
    
    Command<std::string> *get_left_click ()
    {
        return save_left_click_command_;
    }
    Command<std::string> *get_release_left_click ()
    {
        return save_left_release_command_;
    }
    Command<std::string> *get_right_click      ()
    {
        return save_right_click_command_;
    }
    Command<std::string> *set_release_right_click  ()
    {
        return save_right_release_command_;
    }

    void SaveClickLeftEvent(const Event &event)
    {
        if (save_left_click_command_)
        {
            save_left_click_command_->Execute(file_path_);
        }
    }
    void SaveReleasedLeftEvent  (const Event &event)
    {
        if (save_left_release_command_)
        {
            save_left_release_command_->Execute(file_path_);
        }
    }
    void SaveClickRightEvent    (const Event &event) 
    {
        if (save_right_click_command_)
        {
            save_right_click_command_->Execute(file_path_);
        }
    }
    void SaveReleasedRightEvent (const Event &event) 
    {
        if (save_right_release_command_)
        {
            save_right_release_command_->Execute(file_path_);
        }
    }

    void set_file_path(std::string file_path)
    {
        file_path_ = file_path;
    }

    std::string get_path()
    {
        return file_path_;
    }

protected:
    Command<std::string> *save_left_click_command_    = nullptr;
    Command<std::string> *save_left_release_command_  = nullptr;
    Command<std::string> *save_right_click_command_   = nullptr;
    Command<std::string> *save_right_release_command_ = nullptr;  

private:
    std::string file_path_;
};