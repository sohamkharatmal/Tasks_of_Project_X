# Word2Vec (Skip-Gram) Implementation using PyTorch

This project is a simple implementation of the Word2Vec model based on the Skip-Gram architecture from the paper *"Efficient Estimation of Word Representations in Vector Space"* by Mikolov et al.

## What This Project Does

The model learns word embeddings from a small text dataset. It tries to predict the context word given a target word and gradually learns meaningful vector representations for words.

Words that appear in similar contexts end up having similar embeddings.

## Dataset

A small custom text file (`text.txt`) is used for training. It contains simple sentences related to machine learning and AI concepts.

## Approach

- Read and preprocess text data
- Build vocabulary and assign word IDs
- Generate Skip-Gram training pairs
- Define a simple neural network using PyTorch:
  - Embedding layer
  - Linear layer
- Train using CrossEntropyLoss and Adam optimizer
- Update weights using backpropagation
- Evaluate learned embeddings using cosine similarity

## Model Summary

- Model Type: Skip-Gram Word2Vec
- Framework: PyTorch
- Embedding Size: 10
- Loss Function: Cross Entropy Loss
- Optimizer: Adam

## How to Run

```bash
pip install torch numpy
python3 train.py# Tasks_of_Project_X
