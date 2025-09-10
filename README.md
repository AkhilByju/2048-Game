# 2048 Game (C++)

An interactive terminal-based clone of the classic **2048 puzzle game**, written in **C++**.
Players combine tiles with the same number to reach **2048** and beyond, with customizable board sizes, score tracking, and restart functionality.

---

## 🎮 Features

- **Dynamic board size** → choose grid size (e.g., 4x4, 5x5, etc.) at the start or on restart
- **Score & High Score tracking** → keep track of your best runs
- **Restart or Quit anytime** (`R` / `Q`)
- **Game Over detection** → ends when no moves are possible
- **Cross-platform** → works on Mac/Linux/Windows terminal

---

## 🖥️ Demo (Sample Gameplay)

```
=============================
          2048 Game
=============================
Use W (Up), A (Left), S (Down), D (Right) to move tiles.
Combine tiles with the same number to reach 2048!
Press Q to quit the game.
Press R to restart the game.
=============================

Enter board size (e.g., 4 for 4x4): 4

Score: 0  High Score: 0
+-----+-----+-----+-----+
|     |  2  |     |     |
+-----+-----+-----+-----+
|     |     |     |     |
+-----+-----+-----+-----+
|     |     |     |     |
+-----+-----+-----+-----+
|     |     |  2  |     |
+-----+-----+-----+-----+
```

## 🚀 Future Improvements

- Add **colored tiles** using ANSI escape codes for better visuals
- Implement **Undo functionality**
- Add **Win detection (2048 tile)** with option to continue playing
- AI Auto-Player using **Minimax/Expectimax**

---

## 📜 License

This project is licensed under the [MIT License](LICENSE).
