open Rekube;

open Kubernetes.Definitions.Api.Apps.V1;
open Kubernetes.Definitions.Api.Core.V1;
module Metadata = Kubernetes.Definitions.Apimachinery.Pkg.Apis.Meta.V1.Object_meta;
module Label_selector = Kubernetes.Definitions.Apimachinery.Pkg.Apis.Meta.V1.Label_selector;
let quantity = Kubernetes.Definitions.Apimachinery.Pkg.Api.Resource.Quantity.make;

let name = "my-app";

let deployment = (~replicas=1, ~namespace): Deployment.t => {
  let metadata =
    Metadata {"name": name, "namespace": namespace, "labels": [("app", name)]};
  Deployment {
    "metadata": metadata,
    "spec": Deployment_spec {
      "replicas": replicas,
      "selector": Label_selector {
        "match_labels": [("app", name)]
      },
      "template": Pod_template_spec {
          "metadata": metadata,
          "spec": Pod_spec {
            "containers": [
              Container {
                "name": name,
                "image": "gcr.io/hello-minikube-zero-install/hello-node",
                "ports": [Container_port {"name": "app", "container_port": 8080}],
                "resources": Resource_requirements {
                  "requests": [("cpu", quantity("100m")), ("memory", quantity("500Mi"))],
                  "limits": [("cpu", quantity("500m")), ("memory", quantity("1Gi"))],
                },
              },
            ],
          },
        },
      },
  };
};

deployment(~replicas=2, ~namespace="production")
|> Deployment.to_yojson
|> Yojson.Safe.pretty_to_channel(stdout);