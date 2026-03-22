# MPU6050 STL Viewer / STL Prohlížeč

> 🇬🇧 [English](#english) | 🇨🇿 [Česky](#česky)

---

<a name="english"></a>
# 🇬🇧 English

A real-time 3D model viewer that rotates a loaded STL file based on orientation data from an **MPU6050 gyroscope sensor** connected via an **ESP32** microcontroller, using the **Web Serial API**.

---

## 📋 Requirements

### Hardware
- ESP32 development board (e.g. ESP32 DevKit v1)
- MPU6050 gyroscope/accelerometer module
- USB cable

### Wiring

| MPU6050 | ESP32 |
|---------|-------|
| VCC     | 3.3V  |
| GND     | GND   |
| SDA     | GPIO 21 |
| SCL     | GPIO 22 |

### Software
- [Arduino IDE](https://www.arduino.cc/en/software) with ESP32 board support
- Library: [`MPU6050_tockn`](https://github.com/tockn/MPU6050_tockn) (install via Library Manager)
- A **Chromium-based browser** (Chrome, Edge) — required for Web Serial API support

---

## 🚀 Getting Started

### 1. Flash the ESP32

Open the Arduino sketch and upload it to your ESP32:

```cpp
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false);
}

void loop() {
  mpu6050.update();
  Serial.print(mpu6050.getAngleX());
  Serial.print(",");
  Serial.print(mpu6050.getAngleY());
  Serial.print(",");
  Serial.println(mpu6050.getAngleZ());
  delay(20);
}
```

The ESP32 continuously sends angle data over Serial at **115200 baud** in the format:
```
angleX,angleY,angleZ\n
```

### 2. Open the Viewer

Open the `mpu.html` file in **Google Chrome** or **Microsoft Edge**.

> ⚠️ The Web Serial API does **not** work in Firefox or Safari.

### 3. Connect the ESP32

1. Click **"Connect ESP32"**
2. Select your ESP32's COM port from the browser dialog
3. The button will disappear and the **"Reset Model"** button will appear

### 4. Load a STL File

Use the file input to upload any `.stl` file. The model will be centered and displayed automatically.

### 5. Calibrate / Reset Orientation

Click **"Reset Model"** to set the current sensor orientation as the zero position. The model will snap back to its default pose. You can recalibrate at any time.

---

## 🖱️ Controls

| Input | Action |
|-------|--------|
| **Sensor (MPU6050)** | Rotates the 3D model |
| **Mouse drag** | Free rotation of the scene (OrbitControls) |
| **Mouse scroll** | Zoom in / out |

## 🛠️ How It Works

1. The ESP32 reads fused angle data from the MPU6050 (X, Y, Z axes) and sends it over USB Serial.
2. The browser connects to the serial port using the **Web Serial API**.
3. Incoming angle values are parsed and applied to a Three.js `Group` object that wraps the loaded STL mesh.
4. The **OrbitControls** layer sits on top, letting you also freely rotate the scene with the mouse independently of the sensor.
5. Clicking **Reset Model** stores the current raw sensor values as offsets, effectively zeroing the rotation.

---

## 🐛 Troubleshooting

| Problem | Solution |
|---------|----------|
| Serial port not showing | Make sure no other program (e.g. Arduino Serial Monitor) has the port open |
| Model not rotating | Verify the ESP32 is sending data — check Serial Monitor in Arduino IDE first |
| Browser shows no port dialog | Use Chrome or Edge; Web Serial is not supported in Firefox/Safari |
| Model flips unexpectedly | Click "Reset Model" to recalibrate the zero position |

---

## 📦 Dependencies (CDN)

All JavaScript dependencies are loaded from CDN — no installation needed:

- [Three.js r128](https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js)
- [Three.js STLLoader](https://cdn.jsdelivr.net/gh/mrdoob/three.js@r128/examples/js/loaders/STLLoader.js)
- [Three.js OrbitControls](https://cdn.jsdelivr.net/gh/mrdoob/three.js@r128/examples/js/controls/OrbitControls.js)

---

## 📄 License

MIT License — free to use, modify, and distribute.

---
---

<a name="česky"></a>
# 🇨🇿 Česky

Prohlížeč 3D modelů v reálném čase, který otáčí načteným STL souborem podle dat o orientaci z **gyroskopického senzoru MPU6050** připojeného přes mikrokontrolér **ESP32**, s využitím **Web Serial API**.

---

## 📋 Požadavky

### Hardware
- Vývojová deska ESP32 (např. ESP32 DevKit v1)
- Modul gyroskop/akcelerometr MPU6050
- USB kabel

### Zapojení

| MPU6050 | ESP32   |
|---------|---------|
| VCC     | 3.3V    |
| GND     | GND     |
| SDA     | GPIO 21 |
| SCL     | GPIO 22 |

### Software
- [Arduino IDE](https://www.arduino.cc/en/software) s podporou desek ESP32
- Knihovna: [`MPU6050_tockn`](https://github.com/tockn/MPU6050_tockn) (nainstalovat přes Library Manager)
- **Prohlížeč na bázi Chromia** (Chrome, Edge) — vyžadováno pro podporu Web Serial API

---

## 🚀 Začínáme

### 1. Nahrání programu do ESP32

Otevři Arduino sketch a nahraj ho do ESP32:

```cpp
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  mpu6050.begin();
  mpu6050.calcGyroOffsets(false);
}

void loop() {
  mpu6050.update();
  Serial.print(mpu6050.getAngleX());
  Serial.print(",");
  Serial.print(mpu6050.getAngleY());
  Serial.print(",");
  Serial.println(mpu6050.getAngleZ());
  delay(20);
}
```

ESP32 průběžně odesílá data o úhlech přes Sériový port rychlostí **115200 baud** ve formátu:
```
uhelX,uhelY,uhelZ\n
```

### 2. Otevření prohlížeče

Otevři soubor `mpu.html` v prohlížeči **Google Chrome** nebo **Microsoft Edge**.

> ⚠️ Web Serial API **nefunguje** ve Firefoxu ani Safari.

### 3. Připojení ESP32

1. Klikni na **„Připojit ESP32"**
2. Ve vyskakovacím okně prohlížeče vyber COM port svého ESP32
3. Tlačítko zmizí a zobrazí se tlačítko **„Nulovat model"**

### 4. Načtení STL souboru

Pomocí tlačítka pro výběr souboru nahraj libovolný `.stl` soubor. Model se automaticky vystředí a zobrazí.

### 5. Kalibrace / Nulování orientace

Klikni na **„Nulovat model"** — aktuální orientace senzoru se nastaví jako nulová poloha. Model se vrátí do výchozí pozice. Kalibrovat lze kdykoli.

---

## 🖱️ Ovládání

| Vstup | Akce |
|-------|------|
| **Senzor (MPU6050)** | Otáčí 3D modelem |
| **Tažení myší** | Volná rotace scény (OrbitControls) |
| **Kolečko myši** | Přiblížení / oddálení (Zoom) |

---

## 📁 Struktura projektu

## 🛠️ Jak to funguje

1. ESP32 čte sloučená data o úhlech (osy X, Y, Z) z MPU6050 a odesílá je přes USB Serial.
2. Prohlížeč se připojí k sériovému portu pomocí **Web Serial API**.
3. Přijatá data jsou zpracována a aplikována na Three.js objekt `Group`, který obaluje načtený STL model.
4. Vrstva **OrbitControls** umožňuje nezávislé otáčení scény myší, odděleně od senzoru.
5. Kliknutí na **„Nulovat model"** uloží aktuální hodnoty senzoru jako offsety — orientace se efektivně vynuluje.

---

## 🐛 Řešení problémů

| Problém | Řešení |
|---------|--------|
| Sériový port se nezobrazuje | Ujisti se, že port nemá otevřený jiný program (např. Arduino Serial Monitor) |
| Model se neotáčí | Ověř, že ESP32 odesílá data — zkontroluj v Arduino Serial Monitoru |
| Prohlížeč nezobrazí dialog pro výběr portu | Použij Chrome nebo Edge; Firefox a Safari Web Serial nepodporují |
| Model se nečekaně převrátí | Klikni na „Nulovat model" pro rekalibraci nulové polohy |

---

## 📦 Závislosti (CDN)

Všechny JavaScriptové závislosti se načítají z CDN — žádná instalace není potřeba:

- [Three.js r128](https://cdnjs.cloudflare.com/ajax/libs/three.js/r128/three.min.js)
- [Three.js STLLoader](https://cdn.jsdelivr.net/gh/mrdoob/three.js@r128/examples/js/loaders/STLLoader.js)
- [Three.js OrbitControls](https://cdn.jsdelivr.net/gh/mrdoob/three.js@r128/examples/js/controls/OrbitControls.js)

---

## 📄 Licence

Licence MIT — volné použití, úpravy i distribuce.
