import pandas as pd
import numpy as np
from neural_network import FC_layer, Relu_layer, mse_loss, neural_network

def prepare_data(filepath):
    df = pd.read_csv(filepath)
    
    cat_cols = df.select_dtypes(include=["object", "category"]).columns
    num_cols = df.select_dtypes(include=["number"]).columns
    
    df[cat_cols] = df[cat_cols].fillna("unknown")
    df[num_cols] = df[num_cols].fillna(df[num_cols].median())
    
    df = pd.get_dummies(df, columns=cat_cols, drop_first=True)
    
    df[num_cols] = (df[num_cols] - df[num_cols].mean()) / df[num_cols].std()
    
    X = df.drop(columns=['SalePrice'])
    Y = df[['SalePrice']]
    
    X_np = X.to_numpy(dtype=np.float32)
    Y_np = Y.to_numpy(dtype=np.float32)
    
    return X_np, Y_np

def train_model(X, Y):
    input_dim = X.shape[1]
    learning_rate = 0.01
    batch_size = 32
    epochs = 100
    
    layers = [
        FC_layer(input_dim, 64, batch_size),
        Relu_layer(),
        FC_layer(64, 32, batch_size),
        Relu_layer(),
        FC_layer(32, 1, batch_size)
    ]
    
    loss_fn = mse_loss()
    
    model = neural_network(layers, loss_fn, batch_size, learning_rate, epochs, X, Y)
    model.train()
    return model

if __name__ == "__main__":
    print("Preparing data...")
    X, Y = prepare_data("train.csv")
    print(f"Data prepared. Features shape: {X.shape}, Target shape: {Y.shape}")
    
    print("\nStarting training...")
    model = train_model(X, Y)
    print("\nTraining complete.")
