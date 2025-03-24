# Maize-and-Blue
**Maize and Blue** is a maze-based desktop game developed in Qt and C++ for the final project in **ECE 370: Advanced Software Techniques in Computer Engineering**.

# 🌽 Maize and Blue — ECE 370 Final Project

**Maize and Blue** is a maze-based desktop game developed in Qt and C++ for the final project in **ECE 370: Advanced Software Techniques in Computer Engineering**. Themed around the historic rivalry between the University of Michigan and Ohio State, this game challenges players to race through a maize-themed maze before time runs out — while dodging traps and avoiding defeat.

> 🧑‍💻 Developed by: Devin Pen  
> 🎓 University of Michigan–Dearborn  
> 📅 December 2023  
> 🛠️ Framework: Qt 6.x

---

## 🎮 Gameplay Summary

- You start on a **Start Screen** with a "Start Game" button.
- Once the game begins, you are placed at the top-left corner of a randomly selected 10x10 **maze**.
- Reach the **end point ("E")** within **15 seconds** to win.
- Hit a **trap** (`2`) and you’ll need to use the **Undo (U)** key to escape.
- If you collide with a **wall** (`1`), you lose instantly.
- Running out of time also results in defeat.

---

## 🎯 Game Features

| Feature                 | Description |
|------------------------|-------------|
| 🎲 Random Maze         | One of four 10x10 handmade mazes is chosen at runtime. |
| ⌛ Countdown Timer      | Game ends in 15 seconds — ticked via `QTimer`. |
| 💣 Traps               | "O"-labeled traps require the use of the undo function. Moves player back. |
| 🔙 Undo System         | Powered by a `QStack`, lets players rewind their last move. |
| 🔊 Audio Effects       | Victory = *"Hail to the Victors"*, Defeat = *Rickroll*. |
| 💡 Player Feedback     | Game uses `QMessageBox` to deliver feedback like collisions, victory, and loss. |
| ⌨️ Controls            | Arrow keys for movement, `U` for undo |

---

## 💻 QT Classes Used

- **Qt Core & GUI Framework**
- `QPainter` — for rendering the maze and player
- `QTimer` — for the countdown
- `QKeyEvent` — for player movement and interaction
- `QStack` — for undo functionality
- `QMediaPlayer` & `QAudioOutput` — for embedded audio playback
- `QMessageBox` — for feedback popups
- `QPushButton` — for the Start Screen

---

## 📃 License

This project was developed for educational purposes and is not licensed for commercial distribution.

---
