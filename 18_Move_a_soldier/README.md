# 🎥 [Watch the Project Demo on YouTube](https://youtube.com/shorts/Zy03Qcka4IY)
## 🎮 Input Filtering & The Game Loop

To animate the soldier, we implemented a professional game loop with input reading, noise filtering, mapping, and a state-based rendering sequence.

### 1. Joystick Noise Filtering (Moving Average)
Raw ADC values from physical joysticks are prone to electrical noise and jitter. To prevent the character from twitching on the screen, we implemented a **Weighted Moving Average Filter**.

Instead of trusting every new raw value immediately, we mix it with the historical data (75% past weight, 25% new weight). 
* **The Analogy:** Imagine 3 lazy people holding the old position, and 1 excited person (the sudden noise) pulling to a new position. We divide the total by 4. If a sudden electrical spike occurs, the 3 "lazy" historical weights absorb the shock, keeping the soldier perfectly stable.

### 2. Mapping & State-Based Rendering
We map the filtered 12-bit ADC value (`0-4095`) to the physical Y-axis of the Nextion display (`0-240` pixels).

To avoid congesting the UART bus, we only trigger a screen update if the joystick actually moved (`if(new_y != old_y)`). The rendering follows the classic flicker-free logic:
1. **Erase:** Draw the character at `old_y` using the background color (White).
2. **Update:** Save `new_y` as the new `old_y`.
3. **Draw:** Draw the character at the new coordinate using the foreground color (Black).

```c
void move_gunner(){
    HAL_ADC_Start(&hadc1);                   
    HAL_ADC_PollForConversion(&hadc1, 100);  
    joy_y = HAL_ADC_GetValue(&hadc1);        

    // 1. Moving Average Filter (75% Old, 25% New)
    filter_joy_y = (filter_joy_y * 3 + joy_y) / 4;

    // 2. Mapping to Screen Y-Axis
    new_y = (filter_joy_y * 240) / 4095;

    // 3. Screen Update (Draw only if moved)
    if(new_y != old_y){
        draw_gunner(20, old_y, COLOR_WHITE); // Step 1: Erase old
        old_y = new_y;                       // Step 2: Update memory
        draw_gunner(20, new_y, COLOR_BLACK); // Step 3: Draw new
    }
    HAL_Delay(10);
}
```
🛑 The Hardware Bottleneck: Why This Project Ends Here
While the software architecture (Object Composition, Offset Math, and Game Loop) works flawlessly, we hit a physical hardware limitation: UART Bandwidth and Lack of Double Buffering.

When moving the fully armed soldier, the screen exhibits severe flickering. This is not a code bug, but a physical limitation of rendering complex primitive geometries over a serial line.

The Bandwidth Math (Why it flickers):
To achieve smooth, flicker-free animation (60 FPS), a screen must refresh every 0.016 seconds (16 ms).

However, rendering our soldier requires drawing 28 individual geometries (lines, circles). Moving it requires erasing 28 geometries and drawing 28 new ones.

Payload: 56 commands per frame × ~28 bytes per command = ~1568 bytes per frame.

Baud Rate: 115200 bps = ~11,520 bytes/sec max speed.

Render Time: 1568 bytes / 11,520 bytes/sec = 0.136 seconds (136 ms) per frame.

Conclusion: It takes 136 ms just to transmit the frame data to the Nextion display. Because Nextion screens draw primitive commands instantly upon receipt (without an invisible background Double Buffer), the human eye clearly sees the 136ms "construction phase" where the character is erased piece by piece and redrawn piece by piece.