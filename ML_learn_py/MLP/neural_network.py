import numpy as np 

class layer:
    def __init__(self):
        pass

    def forward(self, X):
        pass

    def backward(self, dZ):
        pass

    def update(self):
        pass

class FC_layer(layer):
    def __init__(self, input_dim, output_dim, batch_size):
        self.W = np.random.randn(output_dim, input_dim) * 0.01
        self.b = np.zeros((output_dim, 1))
        self.learning_rate = 0.01
        self.m = batch_size
    
    def forward(self, A):
        self.A = A
        self.Z = np.dot(self.W, A) + self.b
        return self.Z
    
    def backward(self, dZ):
        self.dW = 1/self.A.shape[1] * np.dot(dZ, self.A.T)
        self.db = 1/self.A.shape[1] * np.sum(dZ, axis=1, keepdims=True)
        self.dA = np.dot(self.W.T, dZ)
        return self.dA

    def update(self):
        self.W -= self.learning_rate * self.dW
        self.b -= self.learning_rate * self.db

class Relu_layer(layer):
    def __init__(self):
        pass

    def forward(self, Z):
        self.Z = Z
        self.A = np.maximum(0, Z)
        return self.A

    def backward(self, dA):
        self.dZ = dA * (self.Z > 0)
        return self.dZ

    def update(self):
        pass

class sigmoid_layer(layer):
    def __init__(self):
        pass

    def forward(self, Z):
        self.Z = Z
        self.A = 1 / (1 + np.exp(-Z))
        return self.A

    def backward(self, dA):
        self.dZ = dA * self.A * (1 - self.A)
        return self.dZ

    def update(self):
        pass

class softmax_layer(layer):
    def __init__(self):
        pass

    def forward(self, Z):
        self.Z = Z
        self.A = np.exp(Z) / np.sum(np.exp(Z), axis=0)
        return self.A

    def backward(self, dY):
        self.dZ = dY 
        return self.dZ

    def update(self):
        pass


class mse_loss(layer):
    def __init__(self):
        pass

    def forward(self, Y_hat, Y):
        self.Y_hat = Y_hat
        self.Y = Y
        self.loss = np.sum((Y_hat - Y) ** 2)
        return self.loss
    
    def backward(self):
        self.dY_hat = 2 * (self.Y_hat - self.Y)
        return self.dY_hat
    
    def update(self):
        pass

class neural_network:
    def __init__(self, layers, loss, batch_size, learning_rate, epochs, X, Y):
        self.layers = layers
        self.loss = loss
        self.batch_size = batch_size
        self.learning_rate = learning_rate
        self.epochs = epochs
        self.X = X
        self.Y = Y
    
    def forward(self, X):
        A = X
        for layer in self.layers:
            A = layer.forward(A)
        return A
    
    def backward(self, dZ):
        for layer in reversed(self.layers):
            dZ = layer.backward(dZ)
    
    def update(self):
        for layer in self.layers:
            layer.update()
    
    def train(self):
        for epoch in range(self.epochs):
            for i in range(0, self.X.shape[0], self.batch_size):
                X_batch = self.X[i:i+self.batch_size, :].T
                Y_batch = self.Y[i:i+self.batch_size, :].T
                Y_hat = self.forward(X_batch)
                loss = self.loss.forward(Y_hat, Y_batch)
                dZ = self.loss.backward()
                self.backward(dZ)
                self.update()
            if epoch % 10 == 0 or epoch == self.epochs - 1:
                print(f"Epoch {epoch}: Loss = {loss}")
                

