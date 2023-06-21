# LeNet-5 on ZYBO Z7-10 FPGA
---
### Directories
`python` 
* Train the original model and light model.
* Get the data from trained model such as weights and biases.
* Get the input data to be tested and the answer.

`data`
* Created by `python/*_training.ipynb` and `python/get_data_*.ipynb`.
* Trained weights and biases are stored as text. (`*.data`)
* Weights and biases for original model are in `data/origin`.
* Weights and biases for light model are in `data/lite`.

`cplusplus`
* Implemented according to each model and data type.
* `origin` : Original model with floating point data type.
* `floating-point` : Light model with floating point data type.
* `fixed-point` : Light model with fixed point data type.
* `hls-stream` : Light model with `hls::stream` data type. 
* `hls-parallel` : Partially parallel model with `hls::stream` data type.
* `etc` : Analyze result, save input txt file as a binary, determine number of fixed point interger part, or generate weight array.

`hls`
* `dtype` : Compare floating point and fixed point in terms of latency, resource, max frequency through simple function.
* `predict` : Partially parallel model that can be synthesized with HLS, that the top function name is `predict`.

`arm`
* SW driver code that read input, check accuracy, measure latency.
* Read input binary file through SD card.
* Run 10,000 cases to measure accuracy.
* Use the AXI Timer IP on the PL(Programmable Logic) side to measure the latency.

`etc`
* `waveform` : Waveform obtained through Integrated Logic Analyzer (ILA).
* `BlockDesign.pdf` : Block design of programmable logic.
* `LeNet-5.pdf` : Presentation pdf file that summarizes the content of this LeNet-5 project.

---
### Usage

`python`
* Tensorflow must be installed in advance.
* Since the extension of the file is `*.ipynb`, if you use vscode, it is recommended to install `Jupyter` extension.
* If you run all the `*.ipynb` files, `data` folder will be generated.

`cplusplus`
* Each directories can be compiled by the command `make`.
* In most cases, it can be run by the command `./main`.
* Exceptionally, there are three options for `floating-point` directories.
  * Run one input
    * `./main --input=../../data/input_N.data`
    * `./main --i=../../data/input_N.data`
  * Run one input, and print intermediate results.
    * `./main --input=../../data/input_N.data --print=true`
    * `./main --i=../../data/input_N.data -p=true`
  * Run all (Check accuracy and find Max/Min value of intermediate outputs, weights and biases.)
    * `./main --all=true`
    * `./main -a=true`

---

