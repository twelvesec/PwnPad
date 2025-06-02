![img](https://github.com/twelvesec/PwnPad/blob/main/docs/img/pwnpad.gif?raw=true)
# PwnPad: A Hardware Hacking Learning Platform


## 🎯 Goals

**PwnPad** was created for anyone curious about hardware hacking, no prior experience required. The project is designed to be as affordable and accessible as possible: you can build the entire setup for **under \$20**, and complete all existing challenges using about **\$50 worth of basic tools**.

Through hands-on learning, PwnPad guides you from the very beginning — including PCB manufacturing, soldering, and firmware extraction, all the way to advanced exploitation techniques. You'll gain practical experience with:

* Serial communication protocols like **UART**, **SPI**, and **I2C**
* **Firmware extraction** via ISP and EEPROM dumps
* Building your own **ISP programmer**
* Performing **voltage fault injections** and **timing-based side-channel attacks**

A key feature of PwnPad is its **challenge selector via jumper pins**, no need to reflash the device when switching between challenges. Simply set the pins to load a different challenge from the pre-flashed firmware.

PwnPad aims to bridge the gap between theory and practice by offering a structured, hands-on path into the world of embedded systems and hardware security.



## 📦 Folder Overview

| Folder        | Description                            |
| ------------- | -------------------------------------- |
| `firmware/`   | Firmware for each challenge            |
| `hardware/`   | Schematics, PCB layout, BOM, 3D Models | 
| `challenges/` | Learning objectives per challenge      |
| `tools/`      | Scripts for building/flashing          |
| `docs/`       | Miscellaneous resources                |



## 🔍 Challenges Overview

>⚠️ **Important:**  
>To consider a challenge complete, you must fulfill the goals outlined in the corresponding folder inside `challenges/`.  
>Except for **Code Heist** and **Hard Leak**, **all flags must be retrieved through a serial interface** (UART or I2C).

|#|Name|Topics|Description|
|---|---|---|---|
|1|Serial Snitch|`#UART`|Intercept and decode UART communication.|
|2|Echo Chamber|`#UART`|Intercept and decode UART communication, with security through obscurity.|
|3|Bus Whisperer|`#I2C`|Spy on I2C traffic to extract secrets.|
|4|Invisible Wires|`#I2C`|Attack I2C when slave devices are missing.|
|5|Code Heist|`#SPI` `#ISP` `Flash` `#UART`|Dump and analyze firmware from flash.|
|6|Hard Leak|`#SPI` `#ISP` `EEPROM`|Extract data from the internal EEPROM.|
|7|Power Trip|`#FaultInjection` `#UART`|Use glitching to bypass dead code statements.|
|8|Glitch Storm|`#FaultInjection` `#UART`|Use glitching to bypass password verification.|
|9|Clock Spy|`#SideChannel` `#UART`|Leak secrets using timing variations.|
|10|Tempo Leak|`#SideChannel` `#UART`|Leak secrets using timing variations with a twist.|
|11|Chaos Chain: Glitchgate|`#FaultInjection` `#UART` |Combine UART and glitch attacks to break in.|
|12|Chaos Chain: Timebomb|`#UART` `#SideChannel`|Combine UART and chain timing leaks to break in.|

## 🚀 Getting Started

You can find the complete building instructions in the file: `docs/PwnPad_building_instruction.pdf`

### 🔬 Recommended Equipment For Solving The Challenges
- Multimeter
- Arduino UNO
- Logic Analyzer
- Jumper Wires
- Raspberry Pi Pico & MOSFET for the voltage fault injection challenges.

### 🕹️ How to Play

Once you've assembled and flashed your PwnPad, navigate to the challenges/ directory and open the objective file for the specific gamified challenge you want to play.

To get started, simply configure the jumpers as described in the challenge instructions and press the RESET button on your PwnPad.

For instance, to play the challenge "Serial Snitch", go to challenges/Serial Snitch.md and set the jumper pins as shown in the image below:

![img](https://github.com/twelvesec/PwnPad/blob/main/docs/img/modeselect-example.png?raw=true)

````md
# **Challenge 1: "Serial Snitch"**

As a skilled hardware hacker, you've intercepted a mysterious device recovered from a rogue tech syndicate. The device, dubbed **"Specter-1"**, controls access to a secret underground server, but its interface remains locked behind an unknown UART configuration.

Your mission is clear:

1. **Identify the UART pins** you've uncovered during your investigation.
2. **Determine the correct baud rate** to establish a stable connection.
3. **Access the device’s command interface** and unlock control over the system’s lighting grid.

## Challenge Select
1 --> 1
2 --> 0
3 --> 0
4 --> 0
5 --> 0
```` 

If you'd like to track your challenge progress and submit flags, run:


```bash
bash ./tools/webapp/start.sh
```
Then open your browser and navigate to: `http://127.0.0.1:12530`

![img](https://github.com/twelvesec/PwnPad/blob/main/docs/img/submitpage.png?raw=true)

There you can submit your flags and monitor your progress.

# 🤝 How to Contribute

We ❤️ community contributions! If you’d like to add a new hardware challenge to **PwnPad**, follow the steps below to keep things consistent and functional.

### 🧩 Create a New Challenge

1. **Add a Header File**  
   Create a new header file named something like `challenge13.h`.

2. **Define Your Challenge Function**  
   Inside the header file, define your challenge function using this template:

   ```cpp
   void challenge_template(void) {
       // Initialize I/O

       while (1) {
           // Your Main Challenge Logic
       }
   }
   ```

### 🔀 Register Your Challenge

3. **Update the Main Switch**  
   In `PwnPad.ino`, locate the `switch` statement used for challenge selection. Add a new `case` for your challenge number, and call your function from there.

4. **Challenge Selector Logic**  
   The challenge selection is handled using **5 binary jumper pins**, where:
   - **Pin 1** = Least Significant Bit (LSB)  
   - **Pin 5** = Most Significant Bit (MSB)  

   For example:  
   ```
   Binary: 00011 → Decimal: 3 → Selects Challenge 3
   ```

Make sure your challenge is self-contained, documented, and has clear **goals** in its own folder.

Let’s build awesome open-source hardware hacking content together!


## 🪪 Licensing

This project is licensed under the **GNU General Public License v3.0**. See [LICENSE](LICENSE) for full text.

---

![img](https://github.com/twelvesec/PwnPad/blob/main/docs/img/pwnpad-board.png?raw=true)
