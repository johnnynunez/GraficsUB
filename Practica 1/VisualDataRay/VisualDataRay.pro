TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += qt

INCLUDEPATH += /opt/X11/include
LIBPATH += /opt/X11/lib
LIBS += -lGL
LIBS += -lglut

SOURCES += \
    Scene.cpp \
    Object.cpp \
    Camera.cpp \
    Hitable.cpp \
    Material.cpp \
    Sphere.cpp \
    Lambertian.cpp \
    BoundaryObject.cpp \
    ReadFile.cpp \
    Cara.cpp \
    Render.cpp \
    RayTracingPPM.cpp \
    RayTracingGLU.cpp \
    Animation.cpp \
    TG.cpp \
    Translate.cpp \
    Plane.cpp \
    ColorMapStatic.cpp \
    SceneFactoryTemporal.cpp \
    SceneFactoryStatic.cpp \
    SceneFactory.cpp \
    RayTracingTemps.cpp \
    RenderFactory.cpp \
    Controller.cpp \
    Main.cpp \
    ObjectFactory.cpp \
    Triangle.cpp \
    Cilindre.cpp \
    Circle.cpp \
    Scale.cpp \
    Light.cpp \
    Ground.cpp \
    Metal.cpp \
    Transparent.cpp \
    Cube.cpp \
    Texture.cpp \
    FittedPlane.cpp \
    MaterialTextura.cpp \
    LightVolumetric.cpp \
    LightPuntual.cpp


include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    Object.h \
    Ray.h \
    Scene.h \
    Camera.h \
    Hitable.h \
    Sphere.h \
    Material.h \
    Lambertian.h \
    glm/core/_detail.hpp \
    glm/core/_fixes.hpp \
    glm/core/_swizzle.hpp \
    glm/core/_swizzle_func.hpp \
    glm/core/_vectorize.hpp \
    glm/core/func_common.hpp \
    glm/core/func_exponential.hpp \
    glm/core/func_geometric.hpp \
    glm/core/func_integer.hpp \
    glm/core/func_matrix.hpp \
    glm/core/func_noise.hpp \
    glm/core/func_packing.hpp \
    glm/core/func_trigonometric.hpp \
    glm/core/func_vector_relational.hpp \
    glm/core/hint.hpp \
    glm/core/intrinsic_common.hpp \
    glm/core/intrinsic_exponential.hpp \
    glm/core/intrinsic_geometric.hpp \
    glm/core/intrinsic_matrix.hpp \
    glm/core/intrinsic_trigonometric.hpp \
    glm/core/intrinsic_vector_relational.hpp \
    glm/core/setup.hpp \
    glm/core/type.hpp \
    glm/core/type_float.hpp \
    glm/core/type_gentype.hpp \
    glm/core/type_half.hpp \
    glm/core/type_int.hpp \
    glm/core/type_mat.hpp \
    glm/core/type_mat2x2.hpp \
    glm/core/type_mat2x3.hpp \
    glm/core/type_mat2x4.hpp \
    glm/core/type_mat3x2.hpp \
    glm/core/type_mat3x3.hpp \
    glm/core/type_mat3x4.hpp \
    glm/core/type_mat4x2.hpp \
    glm/core/type_mat4x3.hpp \
    glm/core/type_mat4x4.hpp \
    glm/core/type_size.hpp \
    glm/core/type_vec.hpp \
    glm/core/type_vec1.hpp \
    glm/core/type_vec2.hpp \
    glm/core/type_vec3.hpp \
    glm/core/type_vec4.hpp \
    glm/gtc/constants.hpp \
    glm/gtc/epsilon.hpp \
    glm/gtc/half_float.hpp \
    glm/gtc/matrix_access.hpp \
    glm/gtc/matrix_integer.hpp \
    glm/gtc/matrix_inverse.hpp \
    glm/gtc/matrix_transform.hpp \
    glm/gtc/noise.hpp \
    glm/gtc/quaternion.hpp \
    glm/gtc/random.hpp \
    glm/gtc/reciprocal.hpp \
    glm/gtc/swizzle.hpp \
    glm/gtc/type_precision.hpp \
    glm/gtc/type_ptr.hpp \
    glm/gtc/ulp.hpp \
    glm/gtx/associated_min_max.hpp \
    glm/gtx/bit.hpp \
    glm/gtx/closest_point.hpp \
    glm/gtx/color_cast.hpp \
    glm/gtx/color_space.hpp \
    glm/gtx/color_space_YCoCg.hpp \
    glm/gtx/compatibility.hpp \
    glm/gtx/component_wise.hpp \
    glm/gtx/constants.hpp \
    glm/gtx/epsilon.hpp \
    glm/gtx/euler_angles.hpp \
    glm/gtx/extend.hpp \
    glm/gtx/extented_min_max.hpp \
    glm/gtx/fast_exponential.hpp \
    glm/gtx/fast_square_root.hpp \
    glm/gtx/fast_trigonometry.hpp \
    glm/gtx/gradient_paint.hpp \
    glm/gtx/handed_coordinate_space.hpp \
    glm/gtx/inertia.hpp \
    glm/gtx/int_10_10_10_2.hpp \
    glm/gtx/integer.hpp \
    glm/gtx/intersect.hpp \
    glm/gtx/log_base.hpp \
    glm/gtx/matrix_cross_product.hpp \
    glm/gtx/matrix_interpolation.hpp \
    glm/gtx/matrix_major_storage.hpp \
    glm/gtx/matrix_operation.hpp \
    glm/gtx/matrix_query.hpp \
    glm/gtx/mixed_product.hpp \
    glm/gtx/multiple.hpp \
    glm/gtx/noise.hpp \
    glm/gtx/norm.hpp \
    glm/gtx/normal.hpp \
    glm/gtx/normalize_dot.hpp \
    glm/gtx/number_precision.hpp \
    glm/gtx/ocl_type.hpp \
    glm/gtx/optimum_pow.hpp \
    glm/gtx/orthonormalize.hpp \
    glm/gtx/perpendicular.hpp \
    glm/gtx/polar_coordinates.hpp \
    glm/gtx/projection.hpp \
    glm/gtx/quaternion.hpp \
    glm/gtx/random.hpp \
    glm/gtx/raw_data.hpp \
    glm/gtx/reciprocal.hpp \
    glm/gtx/rotate_vector.hpp \
    glm/gtx/simd_mat4.hpp \
    glm/gtx/simd_vec4.hpp \
    glm/gtx/spline.hpp \
    glm/gtx/std_based_type.hpp \
    glm/gtx/string_cast.hpp \
    glm/gtx/transform.hpp \
    glm/gtx/transform2.hpp \
    glm/gtx/ulp.hpp \
    glm/gtx/unsigned_int.hpp \
    glm/gtx/vec1.hpp \
    glm/gtx/vector_access.hpp \
    glm/gtx/vector_angle.hpp \
    glm/gtx/vector_query.hpp \
    glm/gtx/verbose_operator.hpp \
    glm/gtx/wrap.hpp \
    glm/virtrev/xstream.hpp \
    glm/ext.hpp \
    glm/glm.hpp \
    BoundaryObject.h \
    ReadFile.h \
    Cara.h \
    SceneFactory.h \
    Render.h \
    RayTracingPPM.h \
    RayTracingGLU.h \
    Animation.h \
    TG.h \
    Translate.h \
    Plane.h \
    SceneFactoryStatic.h \
    SceneFactory.h \
    SceneFactoryTemporal.h \
    ColorMapStatic.h \
    ColorMap.h \
    RayTracingTemps.h \
    RenderFactory.h \
    Controller.h \
    Main.h \
    ObjectFactory.h \
    Triangle.h \
    Cilindre.h \
    Circle.h \
    Scale.h \
    Light.h \
    Ground.h \
    Metal.h \
    Transparent.h \
    Cube.h \
    Texture.h \
    FittedPlane.h \
    MaterialTextura.h \
    LightVolumetric.h \
    LightPuntual.h

RESOURCES += \
    resources.qrc
