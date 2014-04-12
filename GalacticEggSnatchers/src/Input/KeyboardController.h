#pragma once

#include "Input/IInputController.h"

namespace INPUT
{
    //////////////////////////////////////////////////////////////////
    /// @brief  An controller supplying input from keyboard hardware.
    ///         Although multiple instances of this class may be created,
    ///         the same underlying keyboard will be used.
    //////////////////////////////////////////////////////////////////
    class KeyboardController : public IInputController
    {
    public:
        /// @brief  Constructor.
        explicit KeyboardController();
        
        /// @brief  Destructor.
        virtual ~KeyboardController();

        /// @copydoc    IInputController::LeftButtonPressed() const
        virtual bool LeftButtonPressed() const;

        /// @copydoc    IInputController::RightButtonPressed() const
        virtual bool RightButtonPressed() const;

        /// @copydoc    IInputController::FireButtonPressed() const
        virtual bool FireButtonPressed() const;

    private:
        KeyboardController(const KeyboardController& keyboardToCopy);    ///< Private to disallow copying.
        KeyboardController& operator=(const KeyboardController& rhsKeyboard);   ///< Private to disallow copying.
    };
}