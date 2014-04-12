#pragma once

/// @brief  Holds code related to handling user input.
namespace INPUT
{
    //////////////////////////////////////////////////////////////////
    /// @brief  An interface for different types of controllers that provide user input.
    //////////////////////////////////////////////////////////////////
    class IInputController
    {
    public:
        /// @brief  Virtual destructor to allow proper destruction of implementing classes.
        virtual ~IInputController() {};

        /// @brief  Checks if the left button is currently pressed.
        /// @return True if the left button is pressed; false otherwise.
        virtual bool LeftButtonPressed() const = 0;

        /// @brief  Checks if the right button is currently pressed.
        /// @return True if the right button is pressed; false otherwise.
        virtual bool RightButtonPressed() const = 0;

        /// @brief  Checks if the fire button is currently pressed.
        /// @return True if the fire button is pressed; false otherwise.
        virtual bool FireButtonPressed() const = 0;
    };
}