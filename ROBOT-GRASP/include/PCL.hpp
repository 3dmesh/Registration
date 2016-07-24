#pragma once

/************************************************************************/
/* namespace std                                                        */
/************************************************************************/
#include "Common.hpp"

/************************************************************************/
/* namespace pcl                                                        */
/************************************************************************/
#include <Eigen/Core>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/console/print.h>

#include <pcl/common/time.h>
#include <pcl/common/transforms.h>
#include <pcl/features/principal_curvatures.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/fpfh_omp.h>

#include <pcl/visualization/pcl_visualizer.h>

using Eigen::Matrix4f;

struct RegisterParameter {
	//Downsample
	float leaf = 0.01f;
	//RANSAC
	int MaximumIterationsRANSAC = 50000; // Number of RANSAC iterations
	int NumberOfSamples = 5; // Number of points to sample for generating/prerejecting a pose
	int CorrespondenceRandomness = 5; // Number of nearest features to use
	float SimilarityThreshold = 0.7f; // Polygonal edge length similarity threshold
	float MaxCorrespondence = 2.5f; // Inlier threshold
	float InlierFraction = 0.2f;
	//ICP
	double EuclideanEpsilon = 2e-8;
	int MaximumIterationsICP = 1000;
};

/************************************************************************/
/* Typedef                                                              */
/************************************************************************/
typedef pcl::PointNormal PointNT;
typedef pcl::PointCloud<PointNT> PointCloudNT;
typedef pcl::PointXYZ PointT;
typedef pcl::PointCloud<PointT> PointCloudT;
typedef pcl::FPFHSignature33 FeatureT;

typedef pcl::NormalEstimationOMP<PointNT, PointNT> NormalEstimationNT;
typedef pcl::FPFHEstimationOMP<PointNT, PointNT, FeatureT> FeatureEstimationT;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;
typedef pcl::visualization::PointCloudColorHandlerCustom<PointNT> ColorHandlerNT;

/************************************************************************/
/* Output                                                               */
/************************************************************************/
using pcl::console::print_info;
using pcl::console::print_warn;
using pcl::console::print_error;
using pcl::console::print_value;
using pcl::console::print_debug;
using pcl::console::print_highlight;

/************************************************************************/
/* Load model and mesh                                                  */
/************************************************************************/
/**
*  @brief LoadModel: load .pcd file to program, either model or mesh
*  @param model_path   .pcd filepath
*  @param model        load PointCloudT/PointCloudNT to memory
*/
bool  LoadModel(const string model_path, PointCloudT::Ptr &model); //XYZ
bool  LoadModel(const string model_path, PointCloudNT::Ptr &model); //Normal

/************************************************************************/
/* Load grasping region point cloud                                     */
/************************************************************************/
bool loadGraspPcd(const string model_path, PointCloudT::Ptr &grasp);
bool loadGrasp(const string model_path, PointCloudT::Ptr &grasp);

/************************************************************************/
/* Downsample model point cloud                                         */
/************************************************************************/
void Downsample(PointCloudNT::Ptr &model, float leaf);


/************************************************************************/
/* Estimate model curvatures                                            */
/************************************************************************/
void EstimateCurvatures(PointCloudNT::Ptr &model, float radius);

/************************************************************************/
/* Estimate FPFH features                                               */
/************************************************************************/
void EstimateFPFH(PointCloudNT::Ptr &model, FeatureCloudT::Ptr &model_features, float leaf);

/************************************************************************/
/* Output Transformation Matrix                                         */
/************************************************************************/
void print4x4Matrix(const Matrix4f & matrix);

/************************************************************************/
/* Registration with RANSAC and ICP                                     */
/************************************************************************/
/**
*  @brief Registration: register model and mesh with RANSAC+ICP, out Transformation matrix
*  @param model        input 3D points cloud
*  @param mesh         generated by Depth camera and convert to Point Cloud Normal Point
*  @param model_align  output aligned model, which used to reflect to 2D
*  @param leaf		   downsample param
*  @param showGraphic  show graphic result or not
*/
Matrix4f Registration(	PointCloudNT::Ptr &model,
						PointCloudNT::Ptr &mesh,
						PointCloudNT::Ptr &model_align,
						RegisterParameter &para,
						bool showGraphic = true	);

Matrix4f RegistrationNoShow(	PointCloudNT::Ptr &model,
								PointCloudNT::Ptr &mesh,
								PointCloudNT::Ptr &model_align,
								RegisterParameter &para );
	










/*
// Types
typedef pcl::PointNormal PointNT;
typedef pcl::PointCloud<PointNT> PointCloudNT;
typedef pcl::FPFHSignature33 FeatureT;
typedef pcl::PointCloud<FeatureT> FeatureCloudT;

// Align a rigid object to a scene with clutter and occlusions
int pointCloudAlignment(PointCloudNT::Ptr &object, FeatureCloudT::Ptr &object_features,
						PointCloudNT::Ptr &scene, FeatureCloudT::Ptr &scene_features,
						PointCloudNT::Ptr &grasp,
						std::vector<PXCPoint3DF32>& result,
						float leaf, float MaxCorrespondenceDistance, float SimilarityThreshold);

int pointCloudFromRealsense(PointCloudNT::Ptr &scene);

int loadModel(std::string &model_path, PointCloudNT::Ptr &object, FeatureCloudT::Ptr &object_features, float leaf);

int preprocessScene(PointCloudNT::Ptr &scene, FeatureCloudT::Ptr &scene_features, float leaf);

int loadGrasp(std::string &model_path, PointCloudNT::Ptr &grasp);

*/