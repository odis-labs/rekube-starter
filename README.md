# rekube-starter

An example starter project for rekube.

## Quickstart

Install dependencies:
```
$ esy install
```

Build the project:

```
$ esy build
```

Run the generator:

```
$ esy x rekube-gen
```

You should see the following JSON output:

```json
{                  
  "spec": {
    "template": {
      "spec": {
        "containers": [
          {
            "resources": {
              "requests": { "cpu": "100m", "memory": "500Mi" },
              "limits": { "cpu": "500m", "memory": "1Gi" }
            },
            "ports": [ { "name": "app", "containerPort": 8080 } ],
            "name": "my-app",
            "image": "gcr.io/hello-minikube-zero-install/hello-node"
          }
        ]
      },
      "metadata": {
        "namespace": "production",
        "name": "my-app",
        "labels": { "app": "my-app" }
      }
    },
    "selector": { "matchLabels": { "app": "my-app" } },
    "replicas": 2
  },
  "metadata": {
    "namespace": "production",
    "name": "my-app",
    "labels": { "app": "my-app" }
  }
}
```
