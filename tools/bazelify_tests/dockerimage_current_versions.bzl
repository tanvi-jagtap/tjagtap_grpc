# Copyright 2023 The gRPC Authors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""
This file is generated by generate_dockerimage_current_versions_bzl.sh
It makes the info from testing docker image *.current_version files
accessible to bazel builds.
"""

DOCKERIMAGE_CURRENT_VERSIONS = {
    "third_party/rake-compiler-dock/rake_aarch64-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_aarch64-linux@sha256:1e00a00f331ece951ed53d6f317fd82ef7e8e696b41502346b2e85906668fd4d",
    "third_party/rake-compiler-dock/rake_arm64-darwin.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_arm64-darwin@sha256:16bb1a0746215557f5577e4cd289e10cec593d74b5a3033c9bb2ab4bc3c6662f",
    "third_party/rake-compiler-dock/rake_x64-mingw-ucrt.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x64-mingw-ucrt@sha256:ff6cc46721bbfd29e87e227dab180e28f322ecb1c7de3eb0a91b47b1f881a54c",
    "third_party/rake-compiler-dock/rake_x64-mingw32.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x64-mingw32@sha256:11ff94f278d705efc89ef3a401bfdfd56a3460180be902d437d8ce96d4e670fa",
    "third_party/rake-compiler-dock/rake_x86-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86-linux@sha256:49e62627c2aaf0ce6455663824239dda99d0c39cfed0a454e8b0ea502ba66a09",
    "third_party/rake-compiler-dock/rake_x86-mingw32.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86-mingw32@sha256:3611deccc6dc127adb2c6e5cf940f6631b0f17ea27e9966894ffa2e6b9c8dabc",
    "third_party/rake-compiler-dock/rake_x86_64-darwin.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86_64-darwin@sha256:ba8e38140f69ae8febe01f8b168782ec1f15cd2e59dd61719fd1176404138062",
    "third_party/rake-compiler-dock/rake_x86_64-linux.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rake_x86_64-linux@sha256:64d4f1c9c23d5d26f38df101128e466940081183cbeac2ab3fa86f4d5a9d0a97",
    "tools/dockerfile/distribtest/cpp_debian10_aarch64_cross_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cpp_debian10_aarch64_cross_x64@sha256:32588bf15195f201ffd91ba279bc425b5b787712b21dcb41bb390341958c3cdb",
    "tools/dockerfile/distribtest/cpp_debian10_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cpp_debian10_x64@sha256:cf1c89aa534084e0c8a6c90bfec42b66e48be16ae15ee97e2a1e7c7187756f33",
    "tools/dockerfile/distribtest/csharp_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_alpine_x64@sha256:65083a6c7b1e6f18374ac6218a924409dfc6ab526ec627b9a33d81e21c93e025",
    "tools/dockerfile/distribtest/csharp_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_centos7_x64@sha256:ec715dd5fbd621789e7598c8d4ac346a7b4037b0cc83fbb29990dc8e4c1f1a13",
    "tools/dockerfile/distribtest/csharp_debian10_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian10_x64@sha256:a06871dfb9ce26880a38af75961f753123b7f9448947b40f5160ba1a4566ec4d",
    "tools/dockerfile/distribtest/csharp_dotnet31_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_dotnet31_x64@sha256:b7afb4aa2f4ac65df757eb42fa78ee105fdde856feda0a9deeb5afedf87a5410",
    "tools/dockerfile/distribtest/csharp_dotnet5_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_dotnet5_x64@sha256:004e02902825b54c7f0d60eaed0819acf6f10c24853bf8f793001114e9969abd",
    "tools/dockerfile/distribtest/csharp_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_ubuntu2204_x64@sha256:a439f2ccbc666f231e511a8e58eb7f66a3de4820a4d5aded1e62275cf8ac49f0",
    "tools/dockerfile/distribtest/php7_debian10_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php7_debian10_x64@sha256:7791ae6f933d3697e3ff25b238edab52c167e088e35e7435663fa0ba1383587d",
    "tools/dockerfile/distribtest/python_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_alpine_x64@sha256:f072c39a2e47d091a937cdcdf6e5517331b27febce8e864399ce16b35d6cc69d",
    "tools/dockerfile/distribtest/python_arch_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_arch_x64@sha256:2c1adadeb010e107132cf5137f32a2d18727796631245b110cc74f69c07502e1",
    "tools/dockerfile/distribtest/python_bullseye_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_bullseye_x64@sha256:80553398f0c59c1dc186052f4f2deaf18fea582f6d1d166eec6ea298639031fb",
    "tools/dockerfile/distribtest/python_bullseye_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_bullseye_x86@sha256:81300aed2bb5e6b3f9bf9f23ba751e884e0317a9cd79659d37cdef4f1cfd24ca",
    "tools/dockerfile/distribtest/python_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_centos7_x64@sha256:13d8f3ae273ac7dab9b5d486ca08045f6ded866c405ed7bb9d2c87574c1b911b",
    "tools/dockerfile/distribtest/python_dev_alpine3.7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_alpine3.7_x64@sha256:9c1ee0b285cb6cd3b4734e3fc0eaa5fa1ee6230f55d87cc21e7364abb1b8c58c",
    "tools/dockerfile/distribtest/python_dev_arch_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_arch_x64@sha256:29f179ef2083ee6addd57e90f58781fdc1cb5dc3dd3e228da1af38785b921f35",
    "tools/dockerfile/distribtest/python_dev_bullseye_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_bullseye_x64@sha256:6c15bd5c350dbc206f45fb512418db51db9a3b73cc304d1d28f4df38bad5a702",
    "tools/dockerfile/distribtest/python_dev_bullseye_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_bullseye_x86@sha256:0cbb08f31a9d45ccdc41a88e409b215cac69cc1a9b05f456ebd96b398fd8e9ee",
    "tools/dockerfile/distribtest/python_dev_centos7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_centos7_x64@sha256:e32238c1c46a752881c6c165b918cb24bd182e3957dc72c514fdbd3d5c3312ab",
    "tools/dockerfile/distribtest/python_dev_fedora39_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_fedora39_x64@sha256:19e636a63b7d812a0a70b3334ab45ad1593ace4303268eef42c2155770ef08d3",
    "tools/dockerfile/distribtest/python_dev_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_ubuntu2004_x64@sha256:cdae114cff8a07ea5fe8738a5cf786075c78ae2bda886e3cc59bcd4890eb78ee",
    "tools/dockerfile/distribtest/python_dev_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_dev_ubuntu2204_x64@sha256:4fc253b24afa128d6295c4e1ac71ea4f8602c7153f4e2e0f38433c14236ec643",
    "tools/dockerfile/distribtest/python_fedora39_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_fedora39_x64@sha256:f2ad099b0d3553f37077705aaf6d221906fba88f0502e7131024a936ec40f58e",
    "tools/dockerfile/distribtest/python_opensuse_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_opensuse_x64@sha256:962e835125423300b800e0448b698de0ff8397819b90c2a8c15fef281619f1b6",
    "tools/dockerfile/distribtest/python_python38_buster_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_python38_buster_aarch64@sha256:0a93bf2a0303aebe1280bafad69df228b9444af9144c767d8169ecc70fb383f6",
    "tools/dockerfile/distribtest/python_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_ubuntu2004_x64@sha256:288cf72bc98fc384b9352d1f6d258b3513925ffe5746dda7e2e343723dd5f733",
    "tools/dockerfile/distribtest/python_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_ubuntu2204_x64@sha256:6054d639247a93af2b496f3c1ce48f63b2e07f5ba54e025f69bb232a747c644e",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_0.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_0@sha256:05c579d93764f12db1a60fa78a26e0f4d6179e54187a3a531c8ff955001731ec",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_1.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_1@sha256:a48bb08275a588fbcea21b6b6056514b69454f6844bd7db9fd72c796892d02e1",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_2.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_2@sha256:9604f8d07c3ea330cdc1ebe394f67828710bbfef52f0dc144e513e3627279b5a",
    "tools/dockerfile/distribtest/ruby_debian11_x64_ruby_3_3.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64_ruby_3_3@sha256:38f27eb75a55df6e9a7d7a01bca40448d0971faee94d0332324ad85ee7200bac",
    "tools/dockerfile/distribtest/ruby_ubuntu2004_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_ubuntu2004_x64@sha256:d754f48a8119b725613bc3c31548ee8770d9bfddd9f49f00f14651aba8e7f760",
    "tools/dockerfile/distribtest/ruby_ubuntu2204_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_ubuntu2204_x64@sha256:3f0558a0164bd7d41dfdb3d5635951503181bd619fce9ce8d390bdc675444eb3",
    "tools/dockerfile/grpc_artifact_centos6_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_centos6_x64@sha256:3285047265ea2b7c5d4df4c769b2d05f56288d947c75e16d27ae2dee693f791b",
    "tools/dockerfile/grpc_artifact_centos6_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_centos6_x86@sha256:19783239da92208f0f39cf563529cd02e889920497ef81c60d20391fa998af62",
    "tools/dockerfile/grpc_artifact_protoc_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_protoc_aarch64@sha256:a0f6b544c1b2fa75f73b26cb28281917153304e9df2789e93de0732494e6b651",
    "tools/dockerfile/grpc_artifact_python_linux_armv7.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_linux_armv7@sha256:f109d6c22cadb053f6843a66ee827d74f34d6cbf75a32f455a9da099ed1bdc9c",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_aarch64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_aarch64@sha256:3f0407d4db904b35a7665c2222db039994cd0c9bdb1a073a653ff8e6940081c9",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_x64@sha256:89329900ec7fedc57cd89690acd34d07d726f6b896f60df987867737d0a0f5a8",
    "tools/dockerfile/grpc_artifact_python_manylinux2014_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_manylinux2014_x86@sha256:8fce8e094b00935dc1f2640b4c2b10216c5a8711c0f4444efbafcd8c355a75a8",
    "tools/dockerfile/grpc_artifact_python_musllinux_1_1_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_musllinux_1_1_x64@sha256:c8e8eb24942a2910197cf5481d61e7cbce68b57bd6f35fae878b043b1f2c38bb",
    "tools/dockerfile/grpc_artifact_python_musllinux_1_1_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_artifact_python_musllinux_1_1_x86@sha256:c288f83435186ee675d004ee52c93195a51201bf2b5fe92581584d977a2499a3",
    "tools/dockerfile/interoptest/grpc_interop_aspnetcore.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_aspnetcore@sha256:8e2e732e78724a8382c340dca72e7653c5f82c251a3110fa2874cc00ba538878",
    "tools/dockerfile/interoptest/grpc_interop_cxx.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_cxx@sha256:e5a474d33773d52ec6a8abbe2d61ee0c2a9c2b5f48793a5ea3b82c4445becf3f",
    "tools/dockerfile/interoptest/grpc_interop_dart.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_dart@sha256:4915a280788126dad029858eb384dbbef2dc18cadccb434df6450dfd7a4929f2",
    "tools/dockerfile/interoptest/grpc_interop_go.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go@sha256:9d02b61552a93770ebb022f588daf9acd1088d29197fe120e0b082ede73f4584",
    "tools/dockerfile/interoptest/grpc_interop_go1.11.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.11@sha256:f2fe3a0a581c687ee4217bf58fd42b18bb1f63d3d006f1b67379ff553b0e23c6",
    "tools/dockerfile/interoptest/grpc_interop_go1.16.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.16@sha256:3767f47c9d06584c6c07b7ab536e13f3e87550330e6c2652ad288d3a72b0de23",
    "tools/dockerfile/interoptest/grpc_interop_go1.19.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.19@sha256:889e7ff34399a5e16af87940d1eaa239e56da307f7faca3f8f1d28379c2e3df3",
    "tools/dockerfile/interoptest/grpc_interop_go1.8.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.8@sha256:7830a301b37539252c592b9cd7fa30a6142d0afc717a05fc8d2b82c74fb45efe",
    "tools/dockerfile/interoptest/grpc_interop_go1.x.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_go1.x@sha256:9d02b61552a93770ebb022f588daf9acd1088d29197fe120e0b082ede73f4584",
    "tools/dockerfile/interoptest/grpc_interop_http2.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_http2@sha256:e3f247d8038374848fadf7215b841e3575c0b2a4217feb503a79b8004b164c5a",
    "tools/dockerfile/interoptest/grpc_interop_java.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_java@sha256:6c0319bbbf77d6c198f61adf92d205efd33cbd2cccaf914a1af8f2dcb61b16a1",
    "tools/dockerfile/interoptest/grpc_interop_node.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_node@sha256:549a7683cc024fb7ffee807eaa8acb6c2d5a5dd0184a2590f91852804eea39a4",
    "tools/dockerfile/interoptest/grpc_interop_nodepurejs.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_nodepurejs@sha256:62f148c4e8b031d02d445e993a840c53eb61566ad0bc007f1d89a3387d1f73a7",
    "tools/dockerfile/interoptest/grpc_interop_php7.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_php7@sha256:f1d2075309ae93c1da7ed3230899ac934ce8f0cdb0bc3694c6b1a9cf8a314ef3",
    "tools/dockerfile/interoptest/grpc_interop_python.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_python@sha256:b3e62554f360f18672711affb79c509a80083a1ddb8e5221bd3b9823a596d0fb",
    "tools/dockerfile/interoptest/grpc_interop_pythonasyncio.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_pythonasyncio@sha256:c349c6e92d32f42e619134ef34d6d33e33e0aa106ea66388b2c22e4231a7baa6",
    "tools/dockerfile/interoptest/grpc_interop_ruby.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/grpc_interop_ruby@sha256:ce9539e9068b2597d5d43dc2bb7df17b84fd8192759cf7a02132b676ca6fa4ed",
    "tools/dockerfile/interoptest/lb_interop_fake_servers.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/lb_interop_fake_servers@sha256:b89a51dd9147e1293f50ee64dd719fce5929ca7894d3770a3d80dbdecb99fd52",
    "tools/dockerfile/test/android_ndk.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/android_ndk@sha256:e4fd2e0048c4ffd2a04e4a41154ee469ed61e058cb704ee95071f7a3bdad507a",
    "tools/dockerfile/test/bazel.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/bazel@sha256:40a08d78ca161e30ab862ba48037fcaf53e812490a6e427da3832382595da746",
    "tools/dockerfile/test/bazel_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/bazel_arm64@sha256:112e4f5085b43df2c02852f23c665aa5310e5a44ea3f4ae553a21b882a9b56aa",
    "tools/dockerfile/test/binder_transport_apk.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/binder_transport_apk@sha256:c800e2d5feb3f6e9a4b837f4c1eb321892766b1e836b3f9d2e5eab8697734ff6",
    "tools/dockerfile/test/csharp_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian11_arm64@sha256:4d4bc5f15e03f3d3d8fd889670ecde2c66a2e4d2dd9db80733c05c1d90c8a248",
    "tools/dockerfile/test/csharp_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/csharp_debian11_x64@sha256:0763d919b17b4cfe5b65aff3bf911c04e9e4d46d11649858742033facd9f534f",
    "tools/dockerfile/test/cxx_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_alpine_x64@sha256:5beda19bcf186b6c9606f4265e38c99bb4308f25bc0987e0fc15164f3c205232",
    "tools/dockerfile/test/cxx_clang_17_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_clang_17_x64@sha256:f4e88cdfe074ee33abbe01f97f945ded0f144693f1eeac4d541a256a7812a21a",
    "tools/dockerfile/test/cxx_clang_6_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_clang_6_x64@sha256:eebbaf353522d523ec9a7acb34bb3ae194e22ea7493c85c01437719e30da205d",
    "tools/dockerfile/test/cxx_debian11_openssl102_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_openssl102_x64@sha256:477ae0da7ff7faa9cf195c0d32472fec4cf8b7325505c63e00b5c794c9a4b1a7",
    "tools/dockerfile/test/cxx_debian11_openssl111_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_openssl111_x64@sha256:d383e66d4a089f9305768e3037faa2a887ff91565b0f3ddd96985dca94e9754f",
    "tools/dockerfile/test/cxx_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_x64@sha256:9f9285da21c1053ac715027e0cee66c20c70ebf016053328a4cee61ffd37e59b",
    "tools/dockerfile/test/cxx_debian11_x86.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian11_x86@sha256:3f505ad99e52a4b3337fedb413e883bc8e5c1d9c089299c34002b89e01254d3b",
    "tools/dockerfile/test/cxx_debian12_openssl309_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_debian12_openssl309_x64@sha256:f75bb715c4f9464526f9affb410f7965a0b8894516d7d98cd89a4e165ae065b7",
    "tools/dockerfile/test/cxx_gcc_12_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_12_x64@sha256:bbdfe66f27b964f9bfd526646b94a19d904fea52bdb244f32fd4355cc8c4551f",
    "tools/dockerfile/test/cxx_gcc_7_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_7_x64@sha256:fb1924844078f48557d6ab57eac1482f80a3cc216406efc3aeaecab671c886d5",
    "tools/dockerfile/test/cxx_gcc_8_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/cxx_gcc_8_x64@sha256:989ceb4324a6240940d7185ccb581f8eff656d2c8c36d15fa14e3f57f294c913",
    "tools/dockerfile/test/php73_zts_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php73_zts_debian11_x64@sha256:186a96566a9c11adfb198309431086bdb02421121c262a2bf0166e3e9b21fb37",
    "tools/dockerfile/test/php7_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php7_debian11_arm64@sha256:7ee21f253a2ddd255f4f6779cd19818eec6524e78b0bf0a7765339e4aa7347c3",
    "tools/dockerfile/test/php7_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/php7_debian11_x64@sha256:34b02fd66832ebf49601bef95632753e6710a75755401c21332d50056ccd52d2",
    "tools/dockerfile/test/python_alpine_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_alpine_x64@sha256:c541f0ce00ca542ed4ae86870b6b73c929227127c13e532d98a9afd28604b830",
    "tools/dockerfile/test/python_debian11_default_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_debian11_default_arm64@sha256:fccca33a655c7aa89dd7ebd9492cbcc1f636bd2a004cd939d1982cfce3d68326",
    "tools/dockerfile/test/python_debian11_default_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/python_debian11_default_x64@sha256:4c539fc93d343324309939c2964204c90f4054cd9eeed093af315cb0f0ef7c26",
    "tools/dockerfile/test/rbe_ubuntu2004.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/rbe_ubuntu2004@sha256:b3eb1a17b7b091e3c5648a803076b2c40601242ff91c04d55997af6641305f68",
    "tools/dockerfile/test/ruby_debian11_arm64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_arm64@sha256:d2e79919b2e2d4cc36a29682ecb5170641df4fb506cfb453978ffdeb8a841bd9",
    "tools/dockerfile/test/ruby_debian11_x64.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/ruby_debian11_x64@sha256:6e8b4696ba0661f11a31ed0992a94d2efcd889a018f57160f0e2fb62963f3593",
    "tools/dockerfile/test/sanity.current_version": "docker://us-docker.pkg.dev/grpc-testing/testing-images-public/sanity@sha256:f138b3aae124e2d6e1a08c5078fb944db7470deeba17ef083aacf3faf939059e",
}
