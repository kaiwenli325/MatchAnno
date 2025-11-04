<p align="center">
  <table>
    <tr>
      <td>
        <img src=".\Assets\icon.svg" alt="icon" width="100">
      </td>
      <td style="vertical-align: middle; padding-left: 20px;">
        <span style="font-size:50px; font-weight:bold;">MatchAnno</span>
      </td>
    </tr> 
  </table>
</p>

<div align="center">
  <span style="font-size:20px;">A tool for matching points annotation</span>
</div>

<br>

<div align="center">
  <img alt="Static Badge" src="https://img.shields.io/badge/C%2B%2B-%2300599C?logo=cplusplus">
  <img alt="Static Badge" src="https://img.shields.io/badge/Qt-%2341CD52?logo=qt&logoColor=%23FFFFFF">

</div>



<br>
<br>

<div align="center">
  <a href="#description"><span style="font-size:20px;"><b>Description</b></a> |
  <a href="#video-demo"><span style="font-size:20px;"><b>Video demo</b></a> |
  <a href="#installation"><span style="font-size:20px;"><b>Installation</b></a> |
  <a href="#usage"><span style="font-size:20px;"><b>Usage</b></a> |
  <a href="#how-to-build"><span style="font-size:20px;"><b>How to build</b></a> |
  <a href="#citation"><span style="font-size:20px;"><b>Citation</b></a>
</div>

-----

## Description

MatchAnno is a graphical tool for annotating matching points. It is written in C++ and uses Qt for its graphical interface. In image registration tasks, it is often necessary to annotate matching points between two images for training or testing. This software is specifically designed for this task.


## Video demo



## Installation
Pre-built softwares for win and macOS-ARM64 can be downloaded on the Github Release page. No installation is required. Simply download the `.zip` file for your platform, unzip it, and run the `.exe` (for win) or `.app` (for macOS-ARM64) file to start using the software.


## Usage
### Folder structure
To use this tool, ou first need to place a pair of images in a single folder. If you have multiple image pairs, the recommended folder organization is as follows:

```
Your_Data_Root/
├── Pair_Set_A/
│   ├── 001_1.jpg
│   └── 001_2.jpg
├── Pair_Set_B/
│   ├── 002_1.jpg
│   └── 002_1.jpg
└── ...
```

Folders and images can be named freely.


### Annotation process
1. **Open the software**:Double-click the `.exe` or `.app` to open the software. Drag the edges of the software window to freely resize it.
2. **Load a pair of images**: Click the `Load Img` button. In the file selection dialog that appears, select the folder containing an image pair, for instance, `Pair_Set_A` as shown in the [Folder structure](#folder-structure) section. If the folder contains a previous annotation result, the previously marked points will be automatically loaded and displayed.
<p align="center">
<img src=".\Assets\load_img.gif" alt="load_img" width="600">
</p>

3. **Annotate matching points**:
    * Use the mouse wheel to zoom in or zoom out of the image.
    <p align="center">
    <img src=".\Assets\zoom_in_zoom_out.gif" alt="load_img" width="600">
    </p>

    * Click and hold the left mouse button to move the image.
    <p align="center">
    <img src=".\Assets\move_the_img.gif" alt="load_img" width="600">
    </p>

    * Put the cursor over a point and right-click to mark it. Then, right-click on the matching point in another image to complete the pair annotation. The annotated point will be displayed in the list on the right side. Identical sequence numbers indicate that they are a matching pair. Two small images on the right displays all currently annotated points.
    <p align="center">
    <img src=".\Assets\annotate_points.gif" alt="load_img" width="600">
    </p>

    * Clicking an annotated point in the list will automatically move both images on the left to the point's and its matching point's location.
    <p align="center">
    <img src=".\Assets\review_points.gif" alt="load_img" width="600">
    </p>


    * Click the annotated point in the list, then press the `Backspace⬅️` key on your keyboard to remove the annotated pair.
    <p align="center">
    <img src=".\Assets\delete_points.gif" alt="load_img" width="600">
    </p>
  

4. **Save**: Click the `Save` button. The annotation results will be saved in `.json` format in the folder containing the loaded image pair. The contents of the `.json` file are structured as shown below, and the coordinates are organized in the format: `[column, row]`. You can read it using code for further post-processing as needed.
  ```
  {
      "down": {
          "Coordi": [
              [
                  1349.9750484752385,  
                  553.3130359812911
              ],
              [
                  1836.673001500551,
                  1201.7904761854086
              ]
          ],
          "Name": "pair1_002.jpg"
      },
      "up": {
          "Coordi": [
              [
                  984.9388649709111,
                  563.0160178552728
              ],
              [
                  1463.8416464237096,
                  1225.0685882489431
              ]
          ],
          "Name": "pair1_001.tif"
      }
  }
  ```
5. **Repeat Steps 2 to 4 to mark a new image pair.**

## How to build

### Windows
This software was developed on Windows 11 using Visual Studio 2022, with Qt version 6.5.3.

We have provided a CMakeLists.txt file for users to build. To build the software, run the following commands in your command line:
```
# Assuming you are in the project root directory

mkdir build

cd build

cmake .. -G "Visual Studio 17 2022" -A x64

cmake --build . --config Release
```

### MacOS
To build the macOS(ARM64) version of the software, we created and built the project in Qt Creator using our publicly available source code.

You can adopt the same approach, or use any method you prefer, since all the necessary source code is open source.


## Citation
If you find this tool useful, please cite our work:
```
@misc{matchanno,
  title={MatchAnno: a tool for matching points annotation},
  author={Kaiwen Li},
  year={2025},
  publisher={GitHub},
  howpublished={\url{https://github.com/kaiwenli325/MatchAnno}},
}
```
The citation details for our paper will be updated upon acceptance.



