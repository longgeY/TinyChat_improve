# TinyChat_improve

This project addresses the challenge of deploying large language models (LLMs) on **resource-constrained devices** such as laptops, by implementing and evaluating advanced **optimization techniques** to improve inference speed.  

We applied:
- **Loop unrolling**
- **Multithreading**
- **SIMD (Single Instruction, Multiple Data)**

These optimizations collectively reduced the inference time from **12.4 seconds to 1.4 seconds per token**, making LLMs viable for **real-world applications on laptops**.

## 🔭 Future Directions

Further improvements may include:
- **CUDA-based parallelism** to utilize GPU capabilities
- **Loop tiling** for memory-efficient execution
- Generalizing to various LLM architectures for broader applicability

This project not only demonstrates **substantial performance gains**, but also provides a foundation for further innovations in **efficient LLM deployment on edge devices**.
