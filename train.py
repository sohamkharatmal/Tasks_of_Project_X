import torch
import torch.nn as nn
import torch.optim as optim

# Read file
with open("text.txt", "r") as file:
    text = file.read()

words = text.split()

# Vocabulary
vocab = list(set(words))

word_to_idx = {}
idx_to_word = {}

for i, word in enumerate(vocab):
    word_to_idx[word] = i
    idx_to_word[i] = word

# Training pairs
pairs = []

for i in range(len(words) - 1):
    target = word_to_idx[words[i]]
    context = word_to_idx[words[i + 1]]

    pairs.append((target, context))

# Model
class Word2Vec(nn.Module):

    def __init__(self, vocab_size, embedding_dim):
        super().__init__()

        self.embedding = nn.Embedding(
            vocab_size,
            embedding_dim
        )

        self.linear = nn.Linear(
            embedding_dim,
            vocab_size
        )

    def forward(self, x):

        x = self.embedding(x)

        x = self.linear(x)

        return x


# Create model
vocab_size = len(vocab)

model = Word2Vec(
    vocab_size,
    10
)

criterion = nn.CrossEntropyLoss()

optimizer = optim.Adam(
    model.parameters(),
    lr=0.01
)

# Training
epochs = 200

for epoch in range(epochs):

    total_loss = 0

    for target, context in pairs:

        target_tensor = torch.tensor([target])

        context_tensor = torch.tensor([context])

        output = model(target_tensor)

        loss = criterion(
            output,
            context_tensor
        )

        optimizer.zero_grad()

        loss.backward()

        optimizer.step()

        total_loss += loss.item()

    if (epoch + 1) % 20 == 0:

        print(
            f"Epoch {epoch+1}, Loss = {total_loss:.4f}"
        )

print("\nTraining Complete!")

embeddings = model.embedding.weight.data


def cosine_similarity(v1, v2):
    return torch.dot(v1, v2) / (
        torch.norm(v1) * torch.norm(v2)
    )


target_word = "machine"

target_idx = word_to_idx[target_word]

target_vector = embeddings[target_idx]

scores = []

for word in vocab:

    idx = word_to_idx[word]

    if word == target_word:
        continue

    similarity = cosine_similarity(
        target_vector,
        embeddings[idx]
    )

    scores.append(
        (word, similarity.item())
    )

scores.sort(
    key=lambda x: x[1],
    reverse=True
)

print(f"\nMost Similar Words To '{target_word}'\n")

for word, score in scores[:5]:
    print(word, round(score, 4))