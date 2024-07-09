import 'package:flutter/material.dart';
import '../../core/app_export.dart';
import '../../widgets/custom_elevated_button.dart';
import 'package:mushroom_monitoring/routes/app_routes.dart';
import 'package:firebase_core/firebase_core.dart';
//import 'firebase_options.dart';
import 'package:firebase_database/firebase_database.dart';

// void readData() {
//   final database = FirebaseDatabase.instance.ref().child("");

//   database.onValue.listen((event) {
//     DataSnapshot dataSnapshot = event.snapshot;
//     Map<dynamic, dynamic> values = dataSnapshot.value;

//   });
// }

class SlashScreen extends StatelessWidget {
  const SlashScreen({Key? key})
      : super(
          key: key,
        );

  void readData() {
    DatabaseReference databaseReference =
        FirebaseDatabase.instance.ref().child('UsersData');

    databaseReference.onValue.listen((event) {
      DataSnapshot dataSnapshot = event.snapshot;
      Map<dynamic, dynamic> values = dataSnapshot.value as Map;
      values.forEach((key, value) {
        print('Key: $key');
        print('humidity:${values['humidty']}');
      });
    });
  }

  @override
  Widget build(BuildContext context) {
    return SafeArea(
      child: Scaffold(
        body: SizedBox(
          width: double.maxFinite,
          child: Column(
            children: [
              CustomImageView(
                imagePath: ImageConstant.imgShape,
                height: 157.v,
                width: 199.h,
                alignment: Alignment.centerLeft,
              ),
              Spacer(),
              CustomImageView(
                imagePath: ImageConstant.imgUndrawSurveillanceRe8tkl,
                height: 120.v,
                width: 167.h,
              ),
              SizedBox(height: 52.v),
              Text(
                "Mushroom Monitoring System",
                style: theme.textTheme.titleSmall,
              ),
              SizedBox(height: 5.v),
              SizedBox(
                height: 278.v,
                width: 250.h,
                child: Stack(
                  alignment: Alignment.bottomLeft,
                  children: [
                    CustomImageView(
                      imagePath: ImageConstant.imgClipPathGroup,
                      height: 148.v,
                      width: 250.h,
                      alignment: Alignment.center,
                    ),
                    CustomElevatedButton(
                      width: 207.h,
                      text: "CONNECT",
                      onPressed: () {
                        readData();
                        Navigator.pushNamed(context, AppRoutes.homeScreen);
                      },
                      margin: EdgeInsets.only(left: 15.h),
                      buttonTextStyle: theme.textTheme.titleMedium!,
                      alignment: Alignment.bottomLeft,
                    )
                  ],
                ),
              ),
              SizedBox(height: 57.v)
            ],
          ),
        ),
      ),
    );
  }
}
