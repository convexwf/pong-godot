#include "pong_game.h"
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>

// even godot disable this warning in their engine
// about losing data when converting double to real_t
#pragma warning(disable : 4244)

PongGame::PongGame() {
    // prevent rendering from happening in editor
    if (!godot::Engine::get_singleton()->is_editor_hint()) {
        godot::UtilityFunctions::print("Started PongGame in Editor // reloaded");
    }
    else {
        godot::UtilityFunctions::print("Started PongGame");
    }
}

PongGame::~PongGame() {
    godot::UtilityFunctions::print("Closed PongGame");
}

void PongGame::_bind_methods() {
    // i didnt add any specific method , but we could add some , if we wanted to interact with the
    // game through the main menu for example
}

void PongGame::_notification(int inWhat) {
    // godot::UtilityFunctions::print("Notification: ", godot::String::num(inWhat));
}

void PongGame::_ready() {
    if (godot::Engine::get_singleton()->is_editor_hint()) {
        godot::UtilityFunctions::print("This is the editor");
        return;
    }
    godot::UtilityFunctions::print("This is the game");

    body_ball_ = get_node<godot::CharacterBody2D>("ball");
    body_player_ = get_node<godot::CharacterBody2D>("paddle_player");
    body_ai_ = get_node<godot::CharacterBody2D>("paddle_enemy");

    ball_direction_ = godot::Vector2(1, 1).normalized();

    score_board_player_ = get_node<godot::Label>("score_player");
    score_board_ai_ = get_node<godot::Label>("score_enemy");

    if (nullptr != body_ball_ && body_ball_->has_meta("speed")) {
        ball_speed_ = body_ball_->get_meta("speed");
    }
    if (nullptr != body_player_ && body_player_->has_meta("speed")) {
        player_speed_ = body_player_->get_meta("speed");
    }
    if (nullptr != body_ai_ && body_ai_->has_meta("speed")) {
        ai_speed_ = body_ai_->get_meta("speed");
    }

    // ball_pos_ai_score =
    // get_node<godot::Marker2D>("AI_Win_Position")->get_global_position().x;
    // ball_pos_player_score =
    //     get_node<godot::Marker2D>("Player_Win_Position")->get_global_position().x;

    // SpawnBall();
    // }
}

void PongGame::_physics_process(double delta) {
    if (godot::Engine::get_singleton()->is_editor_hint()) {
        return;
    }

    ProcessPlayerMovement(delta);
    ProcessAiMovement(delta);
    ProcessBallMovement(delta);
}

// void PongGame::SpawnBall() {
//     ball_speed = BALL_SPEED_GAME_START;
//     body_ball->set_global_position(ball_spawn_pos->get_global_position());
//     float ball_horizontal_direction = 1;
//     if (godot::UtilityFunctions::randf() >= 0.5) ball_horizontal_direction = -1;

//     ball_direction =
//         godot::Vector2(ball_horizontal_direction, godot::UtilityFunctions::randf_range(-1, 1))
//             .normalized();
// }

void PongGame::UpdateScoreLabel() {
    score_board_player_->set_text(godot::UtilityFunctions::str("Player: ", score_player_));
    score_board_ai_->set_text(godot::UtilityFunctions::str("Enemy: ", score_ai_));
}

void PongGame::ProcessBallMovement(double delta) {
    godot::Ref<godot::KinematicCollision2D> collision_info =
        body_ball_->move_and_collide(ball_direction_ * ball_speed_ * delta);
    if (!collision_info.is_null() && collision_info->get_normal() != godot::Vector2()) {
        // godot::UtilityFunctions::print("Collision detected, normal: ",
        //                                collision_info->get_normal());
        // godot::UtilityFunctions::print("Current direction: ", ball_direction_);
        ball_direction_ = ball_direction_.bounce(collision_info->get_normal());
        ball_direction_ = ball_direction_.normalized();
        // godot::UtilityFunctions::print("New direction: ", ball_direction_);

        if (collision_info->get_collider() == body_player_) {
            score_player_ += 1;
            UpdateScoreLabel();
        }
        else if (collision_info->get_collider() == body_ai_) {
            score_ai_ += 1;
            UpdateScoreLabel();
        }
    }
    // if (body_ball_->get_global_position().x < ball_pos_ai_score) {
    //     score_ai += 1;
    //     UpdateScoreLabel();
    //     SpawnBall();
    // }
    // else if (body_ball_->get_global_position().x > ball_pos_player_score) {
    //     score_player += 1;
    //     UpdateScoreLabel();
    //     SpawnBall();
    // }
}

void PongGame::ProcessPlayerMovement(double delta) {
    if (godot::Input::get_singleton()->is_action_pressed("ui_s")) {
        body_player_->move_and_collide(godot::Vector2(0, 1) * player_speed_ * delta);
    }
    else if (godot::Input::get_singleton()->is_action_pressed("ui_w")) {
        body_player_->move_and_collide(godot::Vector2(0, -1) * player_speed_ * delta);
    }
}

void PongGame::ProcessAiMovement(double delta) {
    godot::Vector2 ai_to_ball_dir =
        body_ai_->get_global_position().direction_to(body_ball_->get_global_position());
    ai_to_ball_dir.x = 0;
    if (ai_to_ball_dir.y > 0.4 || ai_to_ball_dir.y < 0.4)
        if (ai_to_ball_dir.y > 0) {
            ai_to_ball_dir.y = 1;
        }
        else {
            ai_to_ball_dir.y = -1;
        }
    body_ai_->move_and_collide(ai_to_ball_dir * ai_speed_ * delta);
}
