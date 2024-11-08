/*
 * Copyright (C) 2019 Tianjin LINGMO Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/&gt;.
 *
 */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include "interface-generated.h"

#include <string.h>
#ifdef G_OS_UNIX
#  include <gio/gunixfdlist.h>
#endif

typedef struct
{
  GDBusArgInfo parent_struct;
  gboolean use_gvariant;
} _ExtendedGDBusArgInfo;

typedef struct
{
  GDBusMethodInfo parent_struct;
  const gchar *signal_name;
  gboolean pass_fdlist;
} _ExtendedGDBusMethodInfo;

typedef struct
{
  GDBusSignalInfo parent_struct;
  const gchar *signal_name;
} _ExtendedGDBusSignalInfo;

typedef struct
{
  GDBusPropertyInfo parent_struct;
  const gchar *hyphen_name;
  guint use_gvariant : 1;
  guint emits_changed_signal : 1;
} _ExtendedGDBusPropertyInfo;

typedef struct
{
  GDBusInterfaceInfo parent_struct;
  const gchar *hyphen_name;
} _ExtendedGDBusInterfaceInfo;

typedef struct
{
  const _ExtendedGDBusPropertyInfo *info;
  guint prop_id;
  GValue orig_value; /* the value before the change */
} ChangedProperty;

static void
_changed_property_free (ChangedProperty *data)
{
  g_value_unset (&data->orig_value);
  g_free (data);
}

static gboolean
_g_strv_equal0 (gchar **a, gchar **b)
{
  gboolean ret = FALSE;
  guint n;
  if (a == NULL && b == NULL)
    {
      ret = TRUE;
      goto out;
    }
  if (a == NULL || b == NULL)
    goto out;
  if (g_strv_length (a) != g_strv_length (b))
    goto out;
  for (n = 0; a[n] != NULL; n++)
    if (g_strcmp0 (a[n], b[n]) != 0)
      goto out;
  ret = TRUE;
out:
  return ret;
}

static gboolean
_g_variant_equal0 (GVariant *a, GVariant *b)
{
  gboolean ret = FALSE;
  if (a == NULL && b == NULL)
    {
      ret = TRUE;
      goto out;
    }
  if (a == NULL || b == NULL)
    goto out;
  ret = g_variant_equal (a, b);
out:
  return ret;
}

G_GNUC_UNUSED static gboolean
_g_value_equal (const GValue *a, const GValue *b)
{
  gboolean ret = FALSE;
  g_assert (G_VALUE_TYPE (a) == G_VALUE_TYPE (b));
  switch (G_VALUE_TYPE (a))
    {
      case G_TYPE_BOOLEAN:
        ret = (g_value_get_boolean (a) == g_value_get_boolean (b));
        break;
      case G_TYPE_UCHAR:
        ret = (g_value_get_uchar (a) == g_value_get_uchar (b));
        break;
      case G_TYPE_INT:
        ret = (g_value_get_int (a) == g_value_get_int (b));
        break;
      case G_TYPE_UINT:
        ret = (g_value_get_uint (a) == g_value_get_uint (b));
        break;
      case G_TYPE_INT64:
        ret = (g_value_get_int64 (a) == g_value_get_int64 (b));
        break;
      case G_TYPE_UINT64:
        ret = (g_value_get_uint64 (a) == g_value_get_uint64 (b));
        break;
      case G_TYPE_DOUBLE:
        {
          /* Avoid -Wfloat-equal warnings by doing a direct bit compare */
          gdouble da = g_value_get_double (a);
          gdouble db = g_value_get_double (b);
          ret = memcmp (&da, &db, sizeof (gdouble)) == 0;
        }
        break;
      case G_TYPE_STRING:
        ret = (g_strcmp0 (g_value_get_string (a), g_value_get_string (b)) == 0);
        break;
      case G_TYPE_VARIANT:
        ret = _g_variant_equal0 (g_value_get_variant (a), g_value_get_variant (b));
        break;
      default:
        if (G_VALUE_TYPE (a) == G_TYPE_STRV)
          ret = _g_strv_equal0 (g_value_get_boxed (a), g_value_get_boxed (b));
        else
          g_critical ("_g_value_equal() does not handle type %s", g_type_name (G_VALUE_TYPE (a)));
        break;
    }
  return ret;
}

/* ------------------------------------------------------------------------
 * Code for interface cn.lingmoos.interface
 * ------------------------------------------------------------------------
 */

/**
 * SECTION:Interface
 * @title: Interface
 * @short_description: Generated C code for the cn.lingmoos.interface D-Bus interface
 *
 * This section contains code for working with the <link linkend="gdbus-interface-cn-lingmoos-interface.top_of_page">cn.lingmoos.interface</link> D-Bus interface in C.
 */

/* ---- Introspection data for cn.lingmoos.interface ---- */

static const _ExtendedGDBusArgInfo _interface_method_info_transfer_bool_value_IN_ARG_InArg =
{
  {
    -1,
    (gchar *) "InArg",
    (gchar *) "(sb)",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_transfer_bool_value_IN_ARG_pointers[] =
{
  &_interface_method_info_transfer_bool_value_IN_ARG_InArg.parent_struct,
  NULL
};

static const _ExtendedGDBusArgInfo _interface_method_info_transfer_bool_value_OUT_ARG_OutArg =
{
  {
    -1,
    (gchar *) "OutArg",
    (gchar *) "b",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_transfer_bool_value_OUT_ARG_pointers[] =
{
  &_interface_method_info_transfer_bool_value_OUT_ARG_OutArg.parent_struct,
  NULL
};

static const _ExtendedGDBusMethodInfo _interface_method_info_transfer_bool_value =
{
  {
    -1,
    (gchar *) "TransferBoolValue",
    (GDBusArgInfo **) &_interface_method_info_transfer_bool_value_IN_ARG_pointers,
    (GDBusArgInfo **) &_interface_method_info_transfer_bool_value_OUT_ARG_pointers,
    NULL
  },
  "handle-transfer-bool-value",
  FALSE
};

static const _ExtendedGDBusArgInfo _interface_method_info_get_bool_value_IN_ARG_InArg =
{
  {
    -1,
    (gchar *) "InArg",
    (gchar *) "s",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_get_bool_value_IN_ARG_pointers[] =
{
  &_interface_method_info_get_bool_value_IN_ARG_InArg.parent_struct,
  NULL
};

static const _ExtendedGDBusArgInfo _interface_method_info_get_bool_value_OUT_ARG_OutArg =
{
  {
    -1,
    (gchar *) "OutArg",
    (gchar *) "b",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_get_bool_value_OUT_ARG_pointers[] =
{
  &_interface_method_info_get_bool_value_OUT_ARG_OutArg.parent_struct,
  NULL
};

static const _ExtendedGDBusMethodInfo _interface_method_info_get_bool_value =
{
  {
    -1,
    (gchar *) "GetBoolValue",
    (GDBusArgInfo **) &_interface_method_info_get_bool_value_IN_ARG_pointers,
    (GDBusArgInfo **) &_interface_method_info_get_bool_value_OUT_ARG_pointers,
    NULL
  },
  "handle-get-bool-value",
  FALSE
};

static const _ExtendedGDBusArgInfo _interface_method_info_transfer_int_value_IN_ARG_InArg =
{
  {
    -1,
    (gchar *) "InArg",
    (gchar *) "(si)",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_transfer_int_value_IN_ARG_pointers[] =
{
  &_interface_method_info_transfer_int_value_IN_ARG_InArg.parent_struct,
  NULL
};

static const _ExtendedGDBusArgInfo _interface_method_info_transfer_int_value_OUT_ARG_OutArg =
{
  {
    -1,
    (gchar *) "OutArg",
    (gchar *) "b",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_transfer_int_value_OUT_ARG_pointers[] =
{
  &_interface_method_info_transfer_int_value_OUT_ARG_OutArg.parent_struct,
  NULL
};

static const _ExtendedGDBusMethodInfo _interface_method_info_transfer_int_value =
{
  {
    -1,
    (gchar *) "TransferIntValue",
    (GDBusArgInfo **) &_interface_method_info_transfer_int_value_IN_ARG_pointers,
    (GDBusArgInfo **) &_interface_method_info_transfer_int_value_OUT_ARG_pointers,
    NULL
  },
  "handle-transfer-int-value",
  FALSE
};

static const _ExtendedGDBusArgInfo _interface_method_info_get_int_value_IN_ARG_InArg =
{
  {
    -1,
    (gchar *) "InArg",
    (gchar *) "s",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_get_int_value_IN_ARG_pointers[] =
{
  &_interface_method_info_get_int_value_IN_ARG_InArg.parent_struct,
  NULL
};

static const _ExtendedGDBusArgInfo _interface_method_info_get_int_value_OUT_ARG_OutArg =
{
  {
    -1,
    (gchar *) "OutArg",
    (gchar *) "i",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_get_int_value_OUT_ARG_pointers[] =
{
  &_interface_method_info_get_int_value_OUT_ARG_OutArg.parent_struct,
  NULL
};

static const _ExtendedGDBusMethodInfo _interface_method_info_get_int_value =
{
  {
    -1,
    (gchar *) "GetIntValue",
    (GDBusArgInfo **) &_interface_method_info_get_int_value_IN_ARG_pointers,
    (GDBusArgInfo **) &_interface_method_info_get_int_value_OUT_ARG_pointers,
    NULL
  },
  "handle-get-int-value",
  FALSE
};

static const _ExtendedGDBusArgInfo _interface_method_info_transfer_string_value_IN_ARG_InArg =
{
  {
    -1,
    (gchar *) "InArg",
    (gchar *) "(ss)",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_transfer_string_value_IN_ARG_pointers[] =
{
  &_interface_method_info_transfer_string_value_IN_ARG_InArg.parent_struct,
  NULL
};

static const _ExtendedGDBusArgInfo _interface_method_info_transfer_string_value_OUT_ARG_OutArg =
{
  {
    -1,
    (gchar *) "OutArg",
    (gchar *) "b",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_transfer_string_value_OUT_ARG_pointers[] =
{
  &_interface_method_info_transfer_string_value_OUT_ARG_OutArg.parent_struct,
  NULL
};

static const _ExtendedGDBusMethodInfo _interface_method_info_transfer_string_value =
{
  {
    -1,
    (gchar *) "TransferStringValue",
    (GDBusArgInfo **) &_interface_method_info_transfer_string_value_IN_ARG_pointers,
    (GDBusArgInfo **) &_interface_method_info_transfer_string_value_OUT_ARG_pointers,
    NULL
  },
  "handle-transfer-string-value",
  FALSE
};

static const _ExtendedGDBusArgInfo _interface_method_info_get_string_value_IN_ARG_InArg =
{
  {
    -1,
    (gchar *) "InArg",
    (gchar *) "s",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_get_string_value_IN_ARG_pointers[] =
{
  &_interface_method_info_get_string_value_IN_ARG_InArg.parent_struct,
  NULL
};

static const _ExtendedGDBusArgInfo _interface_method_info_get_string_value_OUT_ARG_OutArg =
{
  {
    -1,
    (gchar *) "OutArg",
    (gchar *) "s",
    NULL
  },
  FALSE
};

static const GDBusArgInfo * const _interface_method_info_get_string_value_OUT_ARG_pointers[] =
{
  &_interface_method_info_get_string_value_OUT_ARG_OutArg.parent_struct,
  NULL
};

static const _ExtendedGDBusMethodInfo _interface_method_info_get_string_value =
{
  {
    -1,
    (gchar *) "GetStringValue",
    (GDBusArgInfo **) &_interface_method_info_get_string_value_IN_ARG_pointers,
    (GDBusArgInfo **) &_interface_method_info_get_string_value_OUT_ARG_pointers,
    NULL
  },
  "handle-get-string-value",
  FALSE
};

static const GDBusMethodInfo * const _interface_method_info_pointers[] =
{
  &_interface_method_info_transfer_bool_value.parent_struct,
  &_interface_method_info_get_bool_value.parent_struct,
  &_interface_method_info_transfer_int_value.parent_struct,
  &_interface_method_info_get_int_value.parent_struct,
  &_interface_method_info_transfer_string_value.parent_struct,
  &_interface_method_info_get_string_value.parent_struct,
  NULL
};

static const _ExtendedGDBusInterfaceInfo _interface_interface_info =
{
  {
    -1,
    (gchar *) "cn.lingmoos.interface",
    (GDBusMethodInfo **) &_interface_method_info_pointers,
    NULL,
    NULL,
    NULL
  },
  "interface",
};


/**
 * interface_interface_info:
 *
 * Gets a machine-readable description of the <link linkend="gdbus-interface-cn-lingmoos-interface.top_of_page">cn.lingmoos.interface</link> D-Bus interface.
 *
 * Returns: (transfer none): A #GDBusInterfaceInfo. Do not free.
 */
GDBusInterfaceInfo *
interface_interface_info (void)
{
  return (GDBusInterfaceInfo *) &_interface_interface_info.parent_struct;
}

/**
 * interface_override_properties:
 * @klass: The class structure for a #GObject derived class.
 * @property_id_begin: The property id to assign to the first overridden property.
 *
 * Overrides all #GObject properties in the #Interface interface for a concrete class.
 * The properties are overridden in the order they are defined.
 *
 * Returns: The last property id.
 */
guint
interface_override_properties (GObjectClass *klass, guint property_id_begin)
{
  return property_id_begin - 1;
}



/**
 * Interface:
 *
 * Abstract interface type for the D-Bus interface <link linkend="gdbus-interface-cn-lingmoos-interface.top_of_page">cn.lingmoos.interface</link>.
 */

/**
 * InterfaceIface:
 * @parent_iface: The parent interface.
 * @handle_get_bool_value: Handler for the #Interface::handle-get-bool-value signal.
 * @handle_get_int_value: Handler for the #Interface::handle-get-int-value signal.
 * @handle_get_string_value: Handler for the #Interface::handle-get-string-value signal.
 * @handle_transfer_bool_value: Handler for the #Interface::handle-transfer-bool-value signal.
 * @handle_transfer_int_value: Handler for the #Interface::handle-transfer-int-value signal.
 * @handle_transfer_string_value: Handler for the #Interface::handle-transfer-string-value signal.
 *
 * Virtual table for the D-Bus interface <link linkend="gdbus-interface-cn-lingmoos-interface.top_of_page">cn.lingmoos.interface</link>.
 */

typedef InterfaceIface InterfaceInterface;
G_DEFINE_INTERFACE (Interface, interface, G_TYPE_OBJECT)

static void
interface_default_init (InterfaceIface *iface)
{
  /* GObject signals for incoming D-Bus method calls: */
  /**
   * Interface::handle-transfer-bool-value:
   * @object: A #Interface.
   * @invocation: A #GDBusMethodInvocation.
   * @arg_InArg: Argument passed by remote caller.
   *
   * Signal emitted when a remote caller is invoking the <link linkend="gdbus-method-cn-lingmoos-interface.TransferBoolValue">TransferBoolValue()</link> D-Bus method.
   *
   * If a signal handler returns %TRUE, it means the signal handler will handle the invocation (e.g. take a reference to @invocation and eventually call interface_complete_transfer_bool_value() or e.g. g_dbus_method_invocation_return_error() on it) and no order signal handlers will run. If no signal handler handles the invocation, the %G_DBUS_ERROR_UNKNOWN_METHOD error is returned.
   *
   * Returns: %TRUE if the invocation was handled, %FALSE to let other signal handlers run.
   */
  g_signal_new ("handle-transfer-bool-value",
    G_TYPE_FROM_INTERFACE (iface),
    G_SIGNAL_RUN_LAST,
    G_STRUCT_OFFSET (InterfaceIface, handle_transfer_bool_value),
    g_signal_accumulator_true_handled,
    NULL,
    g_cclosure_marshal_generic,
    G_TYPE_BOOLEAN,
    2,
    G_TYPE_DBUS_METHOD_INVOCATION, G_TYPE_VARIANT);

  /**
   * Interface::handle-get-bool-value:
   * @object: A #Interface.
   * @invocation: A #GDBusMethodInvocation.
   * @arg_InArg: Argument passed by remote caller.
   *
   * Signal emitted when a remote caller is invoking the <link linkend="gdbus-method-cn-lingmoos-interface.GetBoolValue">GetBoolValue()</link> D-Bus method.
   *
   * If a signal handler returns %TRUE, it means the signal handler will handle the invocation (e.g. take a reference to @invocation and eventually call interface_complete_get_bool_value() or e.g. g_dbus_method_invocation_return_error() on it) and no order signal handlers will run. If no signal handler handles the invocation, the %G_DBUS_ERROR_UNKNOWN_METHOD error is returned.
   *
   * Returns: %TRUE if the invocation was handled, %FALSE to let other signal handlers run.
   */
  g_signal_new ("handle-get-bool-value",
    G_TYPE_FROM_INTERFACE (iface),
    G_SIGNAL_RUN_LAST,
    G_STRUCT_OFFSET (InterfaceIface, handle_get_bool_value),
    g_signal_accumulator_true_handled,
    NULL,
    g_cclosure_marshal_generic,
    G_TYPE_BOOLEAN,
    2,
    G_TYPE_DBUS_METHOD_INVOCATION, G_TYPE_STRING);

  /**
   * Interface::handle-transfer-int-value:
   * @object: A #Interface.
   * @invocation: A #GDBusMethodInvocation.
   * @arg_InArg: Argument passed by remote caller.
   *
   * Signal emitted when a remote caller is invoking the <link linkend="gdbus-method-cn-lingmoos-interface.TransferIntValue">TransferIntValue()</link> D-Bus method.
   *
   * If a signal handler returns %TRUE, it means the signal handler will handle the invocation (e.g. take a reference to @invocation and eventually call interface_complete_transfer_int_value() or e.g. g_dbus_method_invocation_return_error() on it) and no order signal handlers will run. If no signal handler handles the invocation, the %G_DBUS_ERROR_UNKNOWN_METHOD error is returned.
   *
   * Returns: %TRUE if the invocation was handled, %FALSE to let other signal handlers run.
   */
  g_signal_new ("handle-transfer-int-value",
    G_TYPE_FROM_INTERFACE (iface),
    G_SIGNAL_RUN_LAST,
    G_STRUCT_OFFSET (InterfaceIface, handle_transfer_int_value),
    g_signal_accumulator_true_handled,
    NULL,
    g_cclosure_marshal_generic,
    G_TYPE_BOOLEAN,
    2,
    G_TYPE_DBUS_METHOD_INVOCATION, G_TYPE_VARIANT);

  /**
   * Interface::handle-get-int-value:
   * @object: A #Interface.
   * @invocation: A #GDBusMethodInvocation.
   * @arg_InArg: Argument passed by remote caller.
   *
   * Signal emitted when a remote caller is invoking the <link linkend="gdbus-method-cn-lingmoos-interface.GetIntValue">GetIntValue()</link> D-Bus method.
   *
   * If a signal handler returns %TRUE, it means the signal handler will handle the invocation (e.g. take a reference to @invocation and eventually call interface_complete_get_int_value() or e.g. g_dbus_method_invocation_return_error() on it) and no order signal handlers will run. If no signal handler handles the invocation, the %G_DBUS_ERROR_UNKNOWN_METHOD error is returned.
   *
   * Returns: %TRUE if the invocation was handled, %FALSE to let other signal handlers run.
   */
  g_signal_new ("handle-get-int-value",
    G_TYPE_FROM_INTERFACE (iface),
    G_SIGNAL_RUN_LAST,
    G_STRUCT_OFFSET (InterfaceIface, handle_get_int_value),
    g_signal_accumulator_true_handled,
    NULL,
    g_cclosure_marshal_generic,
    G_TYPE_BOOLEAN,
    2,
    G_TYPE_DBUS_METHOD_INVOCATION, G_TYPE_STRING);

  /**
   * Interface::handle-transfer-string-value:
   * @object: A #Interface.
   * @invocation: A #GDBusMethodInvocation.
   * @arg_InArg: Argument passed by remote caller.
   *
   * Signal emitted when a remote caller is invoking the <link linkend="gdbus-method-cn-lingmoos-interface.TransferStringValue">TransferStringValue()</link> D-Bus method.
   *
   * If a signal handler returns %TRUE, it means the signal handler will handle the invocation (e.g. take a reference to @invocation and eventually call interface_complete_transfer_string_value() or e.g. g_dbus_method_invocation_return_error() on it) and no order signal handlers will run. If no signal handler handles the invocation, the %G_DBUS_ERROR_UNKNOWN_METHOD error is returned.
   *
   * Returns: %TRUE if the invocation was handled, %FALSE to let other signal handlers run.
   */
  g_signal_new ("handle-transfer-string-value",
    G_TYPE_FROM_INTERFACE (iface),
    G_SIGNAL_RUN_LAST,
    G_STRUCT_OFFSET (InterfaceIface, handle_transfer_string_value),
    g_signal_accumulator_true_handled,
    NULL,
    g_cclosure_marshal_generic,
    G_TYPE_BOOLEAN,
    2,
    G_TYPE_DBUS_METHOD_INVOCATION, G_TYPE_VARIANT);

  /**
   * Interface::handle-get-string-value:
   * @object: A #Interface.
   * @invocation: A #GDBusMethodInvocation.
   * @arg_InArg: Argument passed by remote caller.
   *
   * Signal emitted when a remote caller is invoking the <link linkend="gdbus-method-cn-lingmoos-interface.GetStringValue">GetStringValue()</link> D-Bus method.
   *
   * If a signal handler returns %TRUE, it means the signal handler will handle the invocation (e.g. take a reference to @invocation and eventually call interface_complete_get_string_value() or e.g. g_dbus_method_invocation_return_error() on it) and no order signal handlers will run. If no signal handler handles the invocation, the %G_DBUS_ERROR_UNKNOWN_METHOD error is returned.
   *
   * Returns: %TRUE if the invocation was handled, %FALSE to let other signal handlers run.
   */
  g_signal_new ("handle-get-string-value",
    G_TYPE_FROM_INTERFACE (iface),
    G_SIGNAL_RUN_LAST,
    G_STRUCT_OFFSET (InterfaceIface, handle_get_string_value),
    g_signal_accumulator_true_handled,
    NULL,
    g_cclosure_marshal_generic,
    G_TYPE_BOOLEAN,
    2,
    G_TYPE_DBUS_METHOD_INVOCATION, G_TYPE_STRING);

}

/**
 * interface_call_transfer_bool_value:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied or %NULL.
 * @user_data: User data to pass to @callback.
 *
 * Asynchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.TransferBoolValue">TransferBoolValue()</link> D-Bus method on @proxy.
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_call_transfer_bool_value_finish() to get the result of the operation.
 *
 * See interface_call_transfer_bool_value_sync() for the synchronous, blocking version of this method.
 */
void
interface_call_transfer_bool_value (
    Interface *proxy,
    GVariant *arg_InArg,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_dbus_proxy_call (G_DBUS_PROXY (proxy),
    "TransferBoolValue",
    g_variant_new ("(@(sb))",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    callback,
    user_data);
}

/**
 * interface_call_transfer_bool_value_finish:
 * @proxy: A #InterfaceProxy.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_call_transfer_bool_value().
 * @error: Return location for error or %NULL.
 *
 * Finishes an operation started with interface_call_transfer_bool_value().
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_transfer_bool_value_finish (
    Interface *proxy,
    gboolean *out_OutArg,
    GAsyncResult *res,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_finish (G_DBUS_PROXY (proxy), res, error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_transfer_bool_value_sync:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL.
 *
 * Synchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.TransferBoolValue">TransferBoolValue()</link> D-Bus method on @proxy. The calling thread is blocked until a reply is received.
 *
 * See interface_call_transfer_bool_value() for the asynchronous version of this method.
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_transfer_bool_value_sync (
    Interface *proxy,
    GVariant *arg_InArg,
    gboolean *out_OutArg,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "TransferBoolValue",
    g_variant_new ("(@(sb))",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_get_bool_value:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied or %NULL.
 * @user_data: User data to pass to @callback.
 *
 * Asynchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.GetBoolValue">GetBoolValue()</link> D-Bus method on @proxy.
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_call_get_bool_value_finish() to get the result of the operation.
 *
 * See interface_call_get_bool_value_sync() for the synchronous, blocking version of this method.
 */
void
interface_call_get_bool_value (
    Interface *proxy,
    const gchar *arg_InArg,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_dbus_proxy_call (G_DBUS_PROXY (proxy),
    "GetBoolValue",
    g_variant_new ("(s)",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    callback,
    user_data);
}

/**
 * interface_call_get_bool_value_finish:
 * @proxy: A #InterfaceProxy.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_call_get_bool_value().
 * @error: Return location for error or %NULL.
 *
 * Finishes an operation started with interface_call_get_bool_value().
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_get_bool_value_finish (
    Interface *proxy,
    gboolean *out_OutArg,
    GAsyncResult *res,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_finish (G_DBUS_PROXY (proxy), res, error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_get_bool_value_sync:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL.
 *
 * Synchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.GetBoolValue">GetBoolValue()</link> D-Bus method on @proxy. The calling thread is blocked until a reply is received.
 *
 * See interface_call_get_bool_value() for the asynchronous version of this method.
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_get_bool_value_sync (
    Interface *proxy,
    const gchar *arg_InArg,
    gboolean *out_OutArg,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "GetBoolValue",
    g_variant_new ("(s)",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_transfer_int_value:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied or %NULL.
 * @user_data: User data to pass to @callback.
 *
 * Asynchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.TransferIntValue">TransferIntValue()</link> D-Bus method on @proxy.
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_call_transfer_int_value_finish() to get the result of the operation.
 *
 * See interface_call_transfer_int_value_sync() for the synchronous, blocking version of this method.
 */
void
interface_call_transfer_int_value (
    Interface *proxy,
    GVariant *arg_InArg,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_dbus_proxy_call (G_DBUS_PROXY (proxy),
    "TransferIntValue",
    g_variant_new ("(@(si))",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    callback,
    user_data);
}

/**
 * interface_call_transfer_int_value_finish:
 * @proxy: A #InterfaceProxy.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_call_transfer_int_value().
 * @error: Return location for error or %NULL.
 *
 * Finishes an operation started with interface_call_transfer_int_value().
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_transfer_int_value_finish (
    Interface *proxy,
    gboolean *out_OutArg,
    GAsyncResult *res,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_finish (G_DBUS_PROXY (proxy), res, error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_transfer_int_value_sync:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL.
 *
 * Synchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.TransferIntValue">TransferIntValue()</link> D-Bus method on @proxy. The calling thread is blocked until a reply is received.
 *
 * See interface_call_transfer_int_value() for the asynchronous version of this method.
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_transfer_int_value_sync (
    Interface *proxy,
    GVariant *arg_InArg,
    gboolean *out_OutArg,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "TransferIntValue",
    g_variant_new ("(@(si))",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_get_int_value:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied or %NULL.
 * @user_data: User data to pass to @callback.
 *
 * Asynchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.GetIntValue">GetIntValue()</link> D-Bus method on @proxy.
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_call_get_int_value_finish() to get the result of the operation.
 *
 * See interface_call_get_int_value_sync() for the synchronous, blocking version of this method.
 */
void
interface_call_get_int_value (
    Interface *proxy,
    const gchar *arg_InArg,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_dbus_proxy_call (G_DBUS_PROXY (proxy),
    "GetIntValue",
    g_variant_new ("(s)",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    callback,
    user_data);
}

/**
 * interface_call_get_int_value_finish:
 * @proxy: A #InterfaceProxy.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_call_get_int_value().
 * @error: Return location for error or %NULL.
 *
 * Finishes an operation started with interface_call_get_int_value().
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_get_int_value_finish (
    Interface *proxy,
    gint *out_OutArg,
    GAsyncResult *res,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_finish (G_DBUS_PROXY (proxy), res, error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(i)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_get_int_value_sync:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL.
 *
 * Synchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.GetIntValue">GetIntValue()</link> D-Bus method on @proxy. The calling thread is blocked until a reply is received.
 *
 * See interface_call_get_int_value() for the asynchronous version of this method.
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_get_int_value_sync (
    Interface *proxy,
    const gchar *arg_InArg,
    gint *out_OutArg,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "GetIntValue",
    g_variant_new ("(s)",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(i)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_transfer_string_value:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied or %NULL.
 * @user_data: User data to pass to @callback.
 *
 * Asynchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.TransferStringValue">TransferStringValue()</link> D-Bus method on @proxy.
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_call_transfer_string_value_finish() to get the result of the operation.
 *
 * See interface_call_transfer_string_value_sync() for the synchronous, blocking version of this method.
 */
void
interface_call_transfer_string_value (
    Interface *proxy,
    GVariant *arg_InArg,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_dbus_proxy_call (G_DBUS_PROXY (proxy),
    "TransferStringValue",
    g_variant_new ("(@(ss))",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    callback,
    user_data);
}

/**
 * interface_call_transfer_string_value_finish:
 * @proxy: A #InterfaceProxy.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_call_transfer_string_value().
 * @error: Return location for error or %NULL.
 *
 * Finishes an operation started with interface_call_transfer_string_value().
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_transfer_string_value_finish (
    Interface *proxy,
    gboolean *out_OutArg,
    GAsyncResult *res,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_finish (G_DBUS_PROXY (proxy), res, error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_transfer_string_value_sync:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL.
 *
 * Synchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.TransferStringValue">TransferStringValue()</link> D-Bus method on @proxy. The calling thread is blocked until a reply is received.
 *
 * See interface_call_transfer_string_value() for the asynchronous version of this method.
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_transfer_string_value_sync (
    Interface *proxy,
    GVariant *arg_InArg,
    gboolean *out_OutArg,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "TransferStringValue",
    g_variant_new ("(@(ss))",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(b)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_get_string_value:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied or %NULL.
 * @user_data: User data to pass to @callback.
 *
 * Asynchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.GetStringValue">GetStringValue()</link> D-Bus method on @proxy.
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_call_get_string_value_finish() to get the result of the operation.
 *
 * See interface_call_get_string_value_sync() for the synchronous, blocking version of this method.
 */
void
interface_call_get_string_value (
    Interface *proxy,
    const gchar *arg_InArg,
    GCancellable *cancellable,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  g_dbus_proxy_call (G_DBUS_PROXY (proxy),
    "GetStringValue",
    g_variant_new ("(s)",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    callback,
    user_data);
}

/**
 * interface_call_get_string_value_finish:
 * @proxy: A #InterfaceProxy.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_call_get_string_value().
 * @error: Return location for error or %NULL.
 *
 * Finishes an operation started with interface_call_get_string_value().
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_get_string_value_finish (
    Interface *proxy,
    gchar **out_OutArg,
    GAsyncResult *res,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_finish (G_DBUS_PROXY (proxy), res, error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(s)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_call_get_string_value_sync:
 * @proxy: A #InterfaceProxy.
 * @arg_InArg: Argument to pass with the method invocation.
 * @out_OutArg: (out) (optional): Return location for return parameter or %NULL to ignore.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL.
 *
 * Synchronously invokes the <link linkend="gdbus-method-cn-lingmoos-interface.GetStringValue">GetStringValue()</link> D-Bus method on @proxy. The calling thread is blocked until a reply is received.
 *
 * See interface_call_get_string_value() for the asynchronous version of this method.
 *
 * Returns: (skip): %TRUE if the call succeded, %FALSE if @error is set.
 */
gboolean
interface_call_get_string_value_sync (
    Interface *proxy,
    const gchar *arg_InArg,
    gchar **out_OutArg,
    GCancellable *cancellable,
    GError **error)
{
  GVariant *_ret;
  _ret = g_dbus_proxy_call_sync (G_DBUS_PROXY (proxy),
    "GetStringValue",
    g_variant_new ("(s)",
                   arg_InArg),
    G_DBUS_CALL_FLAGS_NONE,
    -1,
    cancellable,
    error);
  if (_ret == NULL)
    goto _out;
  g_variant_get (_ret,
                 "(s)",
                 out_OutArg);
  g_variant_unref (_ret);
_out:
  return _ret != NULL;
}

/**
 * interface_complete_transfer_bool_value:
 * @object: A #Interface.
 * @invocation: (transfer full): A #GDBusMethodInvocation.
 * @OutArg: Parameter to return.
 *
 * Helper function used in service implementations to finish handling invocations of the <link linkend="gdbus-method-cn-lingmoos-interface.TransferBoolValue">TransferBoolValue()</link> D-Bus method. If you instead want to finish handling an invocation by returning an error, use g_dbus_method_invocation_return_error() or similar.
 *
 * This method will free @invocation, you cannot use it afterwards.
 */
void
interface_complete_transfer_bool_value (
    Interface *object,
    GDBusMethodInvocation *invocation,
    gboolean OutArg)
{
  g_dbus_method_invocation_return_value (invocation,
    g_variant_new ("(b)",
                   OutArg));
}

/**
 * interface_complete_get_bool_value:
 * @object: A #Interface.
 * @invocation: (transfer full): A #GDBusMethodInvocation.
 * @OutArg: Parameter to return.
 *
 * Helper function used in service implementations to finish handling invocations of the <link linkend="gdbus-method-cn-lingmoos-interface.GetBoolValue">GetBoolValue()</link> D-Bus method. If you instead want to finish handling an invocation by returning an error, use g_dbus_method_invocation_return_error() or similar.
 *
 * This method will free @invocation, you cannot use it afterwards.
 */
void
interface_complete_get_bool_value (
    Interface *object,
    GDBusMethodInvocation *invocation,
    gboolean OutArg)
{
  g_dbus_method_invocation_return_value (invocation,
    g_variant_new ("(b)",
                   OutArg));
}

/**
 * interface_complete_transfer_int_value:
 * @object: A #Interface.
 * @invocation: (transfer full): A #GDBusMethodInvocation.
 * @OutArg: Parameter to return.
 *
 * Helper function used in service implementations to finish handling invocations of the <link linkend="gdbus-method-cn-lingmoos-interface.TransferIntValue">TransferIntValue()</link> D-Bus method. If you instead want to finish handling an invocation by returning an error, use g_dbus_method_invocation_return_error() or similar.
 *
 * This method will free @invocation, you cannot use it afterwards.
 */
void
interface_complete_transfer_int_value (
    Interface *object,
    GDBusMethodInvocation *invocation,
    gboolean OutArg)
{
  g_dbus_method_invocation_return_value (invocation,
    g_variant_new ("(b)",
                   OutArg));
}

/**
 * interface_complete_get_int_value:
 * @object: A #Interface.
 * @invocation: (transfer full): A #GDBusMethodInvocation.
 * @OutArg: Parameter to return.
 *
 * Helper function used in service implementations to finish handling invocations of the <link linkend="gdbus-method-cn-lingmoos-interface.GetIntValue">GetIntValue()</link> D-Bus method. If you instead want to finish handling an invocation by returning an error, use g_dbus_method_invocation_return_error() or similar.
 *
 * This method will free @invocation, you cannot use it afterwards.
 */
void
interface_complete_get_int_value (
    Interface *object,
    GDBusMethodInvocation *invocation,
    gint OutArg)
{
  g_dbus_method_invocation_return_value (invocation,
    g_variant_new ("(i)",
                   OutArg));
}

/**
 * interface_complete_transfer_string_value:
 * @object: A #Interface.
 * @invocation: (transfer full): A #GDBusMethodInvocation.
 * @OutArg: Parameter to return.
 *
 * Helper function used in service implementations to finish handling invocations of the <link linkend="gdbus-method-cn-lingmoos-interface.TransferStringValue">TransferStringValue()</link> D-Bus method. If you instead want to finish handling an invocation by returning an error, use g_dbus_method_invocation_return_error() or similar.
 *
 * This method will free @invocation, you cannot use it afterwards.
 */
void
interface_complete_transfer_string_value (
    Interface *object,
    GDBusMethodInvocation *invocation,
    gboolean OutArg)
{
  g_dbus_method_invocation_return_value (invocation,
    g_variant_new ("(b)",
                   OutArg));
}

/**
 * interface_complete_get_string_value:
 * @object: A #Interface.
 * @invocation: (transfer full): A #GDBusMethodInvocation.
 * @OutArg: Parameter to return.
 *
 * Helper function used in service implementations to finish handling invocations of the <link linkend="gdbus-method-cn-lingmoos-interface.GetStringValue">GetStringValue()</link> D-Bus method. If you instead want to finish handling an invocation by returning an error, use g_dbus_method_invocation_return_error() or similar.
 *
 * This method will free @invocation, you cannot use it afterwards.
 */
void
interface_complete_get_string_value (
    Interface *object,
    GDBusMethodInvocation *invocation,
    const gchar *OutArg)
{
  g_dbus_method_invocation_return_value (invocation,
    g_variant_new ("(s)",
                   OutArg));
}

/* ------------------------------------------------------------------------ */

/**
 * InterfaceProxy:
 *
 * The #InterfaceProxy structure contains only private data and should only be accessed using the provided API.
 */

/**
 * InterfaceProxyClass:
 * @parent_class: The parent class.
 *
 * Class structure for #InterfaceProxy.
 */

struct _InterfaceProxyPrivate
{
  GData *qdata;
};

static void interface_proxy_iface_init (InterfaceIface *iface);

#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
G_DEFINE_TYPE_WITH_CODE (InterfaceProxy, interface_proxy, G_TYPE_DBUS_PROXY,
                         G_ADD_PRIVATE (InterfaceProxy)
                         G_IMPLEMENT_INTERFACE (TYPE_INTERFACE, interface_proxy_iface_init))

#else
G_DEFINE_TYPE_WITH_CODE (InterfaceProxy, interface_proxy, G_TYPE_DBUS_PROXY,
                         G_IMPLEMENT_INTERFACE (TYPE_INTERFACE, interface_proxy_iface_init))

#endif
static void
interface_proxy_finalize (GObject *object)
{
  InterfaceProxy *proxy = INTERFACE_PROXY (object);
  g_datalist_clear (&proxy->priv->qdata);
  G_OBJECT_CLASS (interface_proxy_parent_class)->finalize (object);
}

static void
interface_proxy_get_property (GObject      *object,
  guint         prop_id,
  GValue       *value,
  GParamSpec   *pspec G_GNUC_UNUSED)
{
}

static void
interface_proxy_set_property (GObject      *object,
  guint         prop_id,
  const GValue *value,
  GParamSpec   *pspec G_GNUC_UNUSED)
{
}

static void
interface_proxy_g_signal (GDBusProxy *proxy,
  const gchar *sender_name G_GNUC_UNUSED,
  const gchar *signal_name,
  GVariant *parameters)
{
  _ExtendedGDBusSignalInfo *info;
  GVariantIter iter;
  GVariant *child;
  GValue *paramv;
  gsize num_params;
  gsize n;
  guint signal_id;
  info = (_ExtendedGDBusSignalInfo *) g_dbus_interface_info_lookup_signal ((GDBusInterfaceInfo *) &_interface_interface_info.parent_struct, signal_name);
  if (info == NULL)
    return;
  num_params = g_variant_n_children (parameters);
  paramv = g_new0 (GValue, num_params + 1);
  g_value_init (&paramv[0], TYPE_INTERFACE);
  g_value_set_object (&paramv[0], proxy);
  g_variant_iter_init (&iter, parameters);
  n = 1;
  while ((child = g_variant_iter_next_value (&iter)) != NULL)
    {
      _ExtendedGDBusArgInfo *arg_info = (_ExtendedGDBusArgInfo *) info->parent_struct.args[n - 1];
      if (arg_info->use_gvariant)
        {
          g_value_init (&paramv[n], G_TYPE_VARIANT);
          g_value_set_variant (&paramv[n], child);
          n++;
        }
      else
        g_dbus_gvariant_to_gvalue (child, &paramv[n++]);
      g_variant_unref (child);
    }
  signal_id = g_signal_lookup (info->signal_name, TYPE_INTERFACE);
  g_signal_emitv (paramv, signal_id, 0, NULL);
  for (n = 0; n < num_params + 1; n++)
    g_value_unset (&paramv[n]);
  g_free (paramv);
}

static void
interface_proxy_g_properties_changed (GDBusProxy *_proxy,
  GVariant *changed_properties,
  const gchar *const *invalidated_properties)
{
  InterfaceProxy *proxy = INTERFACE_PROXY (_proxy);
  guint n;
  const gchar *key;
  GVariantIter *iter;
  _ExtendedGDBusPropertyInfo *info;
  g_variant_get (changed_properties, "a{sv}", &iter);
  while (g_variant_iter_next (iter, "{&sv}", &key, NULL))
    {
      info = (_ExtendedGDBusPropertyInfo *) g_dbus_interface_info_lookup_property ((GDBusInterfaceInfo *) &_interface_interface_info.parent_struct, key);
      g_datalist_remove_data (&proxy->priv->qdata, key);
      if (info != NULL)
        g_object_notify (G_OBJECT (proxy), info->hyphen_name);
    }
  g_variant_iter_free (iter);
  for (n = 0; invalidated_properties[n] != NULL; n++)
    {
      info = (_ExtendedGDBusPropertyInfo *) g_dbus_interface_info_lookup_property ((GDBusInterfaceInfo *) &_interface_interface_info.parent_struct, invalidated_properties[n]);
      g_datalist_remove_data (&proxy->priv->qdata, invalidated_properties[n]);
      if (info != NULL)
        g_object_notify (G_OBJECT (proxy), info->hyphen_name);
    }
}

static void
interface_proxy_init (InterfaceProxy *proxy)
{
#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
  proxy->priv = interface_proxy_get_instance_private (proxy);
#else
  proxy->priv = G_TYPE_INSTANCE_GET_PRIVATE (proxy, TYPE_INTERFACE_PROXY, InterfaceProxyPrivate);
#endif

  g_dbus_proxy_set_interface_info (G_DBUS_PROXY (proxy), interface_interface_info ());
}

static void
interface_proxy_class_init (InterfaceProxyClass *klass)
{
  GObjectClass *gobject_class;
  GDBusProxyClass *proxy_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize     = interface_proxy_finalize;
  gobject_class->get_property = interface_proxy_get_property;
  gobject_class->set_property = interface_proxy_set_property;

  proxy_class = G_DBUS_PROXY_CLASS (klass);
  proxy_class->g_signal = interface_proxy_g_signal;
  proxy_class->g_properties_changed = interface_proxy_g_properties_changed;

#if GLIB_VERSION_MAX_ALLOWED < GLIB_VERSION_2_38
  g_type_class_add_private (klass, sizeof (InterfaceProxyPrivate));
#endif
}

static void
interface_proxy_iface_init (InterfaceIface *iface)
{
}

/**
 * interface_proxy_new:
 * @connection: A #GDBusConnection.
 * @flags: Flags from the #GDBusProxyFlags enumeration.
 * @name: (nullable): A bus name (well-known or unique) or %NULL if @connection is not a message bus connection.
 * @object_path: An object path.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied.
 * @user_data: User data to pass to @callback.
 *
 * Asynchronously creates a proxy for the D-Bus interface <link linkend="gdbus-interface-cn-lingmoos-interface.top_of_page">cn.lingmoos.interface</link>. See g_dbus_proxy_new() for more details.
 *
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_proxy_new_finish() to get the result of the operation.
 *
 * See interface_proxy_new_sync() for the synchronous, blocking version of this constructor.
 */
void
interface_proxy_new (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data)
{
  g_async_initable_new_async (TYPE_INTERFACE_PROXY, G_PRIORITY_DEFAULT, cancellable, callback, user_data, "g-flags", flags, "g-name", name, "g-connection", connection, "g-object-path", object_path, "g-interface-name", "cn.lingmoos.interface", NULL);
}

/**
 * interface_proxy_new_finish:
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_proxy_new().
 * @error: Return location for error or %NULL
 *
 * Finishes an operation started with interface_proxy_new().
 *
 * Returns: (transfer full) (type InterfaceProxy): The constructed proxy object or %NULL if @error is set.
 */
Interface *
interface_proxy_new_finish (
    GAsyncResult        *res,
    GError             **error)
{
  GObject *ret;
  GObject *source_object;
  source_object = g_async_result_get_source_object (res);
  ret = g_async_initable_new_finish (G_ASYNC_INITABLE (source_object), res, error);
  g_object_unref (source_object);
  if (ret != NULL)
    return INTERFACE (ret);
  else
    return NULL;
}

/**
 * interface_proxy_new_sync:
 * @connection: A #GDBusConnection.
 * @flags: Flags from the #GDBusProxyFlags enumeration.
 * @name: (nullable): A bus name (well-known or unique) or %NULL if @connection is not a message bus connection.
 * @object_path: An object path.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL
 *
 * Synchronously creates a proxy for the D-Bus interface <link linkend="gdbus-interface-cn-lingmoos-interface.top_of_page">cn.lingmoos.interface</link>. See g_dbus_proxy_new_sync() for more details.
 *
 * The calling thread is blocked until a reply is received.
 *
 * See interface_proxy_new() for the asynchronous version of this constructor.
 *
 * Returns: (transfer full) (type InterfaceProxy): The constructed proxy object or %NULL if @error is set.
 */
Interface *
interface_proxy_new_sync (
    GDBusConnection     *connection,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error)
{
  GInitable *ret;
  ret = g_initable_new (TYPE_INTERFACE_PROXY, cancellable, error, "g-flags", flags, "g-name", name, "g-connection", connection, "g-object-path", object_path, "g-interface-name", "cn.lingmoos.interface", NULL);
  if (ret != NULL)
    return INTERFACE (ret);
  else
    return NULL;
}


/**
 * interface_proxy_new_for_bus:
 * @bus_type: A #GBusType.
 * @flags: Flags from the #GDBusProxyFlags enumeration.
 * @name: A bus name (well-known or unique).
 * @object_path: An object path.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @callback: A #GAsyncReadyCallback to call when the request is satisfied.
 * @user_data: User data to pass to @callback.
 *
 * Like interface_proxy_new() but takes a #GBusType instead of a #GDBusConnection.
 *
 * When the operation is finished, @callback will be invoked in the <link linkend="g-main-context-push-thread-default">thread-default main loop</link> of the thread you are calling this method from.
 * You can then call interface_proxy_new_for_bus_finish() to get the result of the operation.
 *
 * See interface_proxy_new_for_bus_sync() for the synchronous, blocking version of this constructor.
 */
void
interface_proxy_new_for_bus (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GAsyncReadyCallback  callback,
    gpointer             user_data)
{
  g_async_initable_new_async (TYPE_INTERFACE_PROXY, G_PRIORITY_DEFAULT, cancellable, callback, user_data, "g-flags", flags, "g-name", name, "g-bus-type", bus_type, "g-object-path", object_path, "g-interface-name", "cn.lingmoos.interface", NULL);
}

/**
 * interface_proxy_new_for_bus_finish:
 * @res: The #GAsyncResult obtained from the #GAsyncReadyCallback passed to interface_proxy_new_for_bus().
 * @error: Return location for error or %NULL
 *
 * Finishes an operation started with interface_proxy_new_for_bus().
 *
 * Returns: (transfer full) (type InterfaceProxy): The constructed proxy object or %NULL if @error is set.
 */
Interface *
interface_proxy_new_for_bus_finish (
    GAsyncResult        *res,
    GError             **error)
{
  GObject *ret;
  GObject *source_object;
  source_object = g_async_result_get_source_object (res);
  ret = g_async_initable_new_finish (G_ASYNC_INITABLE (source_object), res, error);
  g_object_unref (source_object);
  if (ret != NULL)
    return INTERFACE (ret);
  else
    return NULL;
}

/**
 * interface_proxy_new_for_bus_sync:
 * @bus_type: A #GBusType.
 * @flags: Flags from the #GDBusProxyFlags enumeration.
 * @name: A bus name (well-known or unique).
 * @object_path: An object path.
 * @cancellable: (nullable): A #GCancellable or %NULL.
 * @error: Return location for error or %NULL
 *
 * Like interface_proxy_new_sync() but takes a #GBusType instead of a #GDBusConnection.
 *
 * The calling thread is blocked until a reply is received.
 *
 * See interface_proxy_new_for_bus() for the asynchronous version of this constructor.
 *
 * Returns: (transfer full) (type InterfaceProxy): The constructed proxy object or %NULL if @error is set.
 */
Interface *
interface_proxy_new_for_bus_sync (
    GBusType             bus_type,
    GDBusProxyFlags      flags,
    const gchar         *name,
    const gchar         *object_path,
    GCancellable        *cancellable,
    GError             **error)
{
  GInitable *ret;
  ret = g_initable_new (TYPE_INTERFACE_PROXY, cancellable, error, "g-flags", flags, "g-name", name, "g-bus-type", bus_type, "g-object-path", object_path, "g-interface-name", "cn.lingmoos.interface", NULL);
  if (ret != NULL)
    return INTERFACE (ret);
  else
    return NULL;
}


/* ------------------------------------------------------------------------ */

/**
 * InterfaceSkeleton:
 *
 * The #InterfaceSkeleton structure contains only private data and should only be accessed using the provided API.
 */

/**
 * InterfaceSkeletonClass:
 * @parent_class: The parent class.
 *
 * Class structure for #InterfaceSkeleton.
 */

struct _InterfaceSkeletonPrivate
{
  GValue *properties;
  GList *changed_properties;
  GSource *changed_properties_idle_source;
  GMainContext *context;
  GMutex lock;
};

static void
_interface_skeleton_handle_method_call (
  GDBusConnection *connection G_GNUC_UNUSED,
  const gchar *sender G_GNUC_UNUSED,
  const gchar *object_path G_GNUC_UNUSED,
  const gchar *interface_name,
  const gchar *method_name,
  GVariant *parameters,
  GDBusMethodInvocation *invocation,
  gpointer user_data)
{
  InterfaceSkeleton *skeleton = INTERFACE_SKELETON (user_data);
  _ExtendedGDBusMethodInfo *info;
  GVariantIter iter;
  GVariant *child;
  GValue *paramv;
  gsize num_params;
  guint num_extra;
  gsize n;
  guint signal_id;
  GValue return_value = G_VALUE_INIT;
  info = (_ExtendedGDBusMethodInfo *) g_dbus_method_invocation_get_method_info (invocation);
  g_assert (info != NULL);
  num_params = g_variant_n_children (parameters);
  num_extra = info->pass_fdlist ? 3 : 2;  paramv = g_new0 (GValue, num_params + num_extra);
  n = 0;
  g_value_init (&paramv[n], TYPE_INTERFACE);
  g_value_set_object (&paramv[n++], skeleton);
  g_value_init (&paramv[n], G_TYPE_DBUS_METHOD_INVOCATION);
  g_value_set_object (&paramv[n++], invocation);
  if (info->pass_fdlist)
    {
#ifdef G_OS_UNIX
      g_value_init (&paramv[n], G_TYPE_UNIX_FD_LIST);
      g_value_set_object (&paramv[n++], g_dbus_message_get_unix_fd_list (g_dbus_method_invocation_get_message (invocation)));
#else
      g_assert_not_reached ();
#endif
    }
  g_variant_iter_init (&iter, parameters);
  while ((child = g_variant_iter_next_value (&iter)) != NULL)
    {
      _ExtendedGDBusArgInfo *arg_info = (_ExtendedGDBusArgInfo *) info->parent_struct.in_args[n - num_extra];
      if (arg_info->use_gvariant)
        {
          g_value_init (&paramv[n], G_TYPE_VARIANT);
          g_value_set_variant (&paramv[n], child);
          n++;
        }
      else
        g_dbus_gvariant_to_gvalue (child, &paramv[n++]);
      g_variant_unref (child);
    }
  signal_id = g_signal_lookup (info->signal_name, TYPE_INTERFACE);
  g_value_init (&return_value, G_TYPE_BOOLEAN);
  g_signal_emitv (paramv, signal_id, 0, &return_value);
  if (!g_value_get_boolean (&return_value))
    g_dbus_method_invocation_return_error (invocation, G_DBUS_ERROR, G_DBUS_ERROR_UNKNOWN_METHOD, "Method %s is not implemented on interface %s", method_name, interface_name);
  g_value_unset (&return_value);
  for (n = 0; n < num_params + num_extra; n++)
    g_value_unset (&paramv[n]);
  g_free (paramv);
}

static GVariant *
_interface_skeleton_handle_get_property (
  GDBusConnection *connection G_GNUC_UNUSED,
  const gchar *sender G_GNUC_UNUSED,
  const gchar *object_path G_GNUC_UNUSED,
  const gchar *interface_name G_GNUC_UNUSED,
  const gchar *property_name,
  GError **error,
  gpointer user_data)
{
  InterfaceSkeleton *skeleton = INTERFACE_SKELETON (user_data);
  GValue value = G_VALUE_INIT;
  GParamSpec *pspec;
  _ExtendedGDBusPropertyInfo *info;
  GVariant *ret;
  ret = NULL;
  info = (_ExtendedGDBusPropertyInfo *) g_dbus_interface_info_lookup_property ((GDBusInterfaceInfo *) &_interface_interface_info.parent_struct, property_name);
  g_assert (info != NULL);
  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (skeleton), info->hyphen_name);
  if (pspec == NULL)
    {
      g_set_error (error, G_DBUS_ERROR, G_DBUS_ERROR_INVALID_ARGS, "No property with name %s", property_name);
    }
  else
    {
      g_value_init (&value, pspec->value_type);
      g_object_get_property (G_OBJECT (skeleton), info->hyphen_name, &value);
      ret = g_dbus_gvalue_to_gvariant (&value, G_VARIANT_TYPE (info->parent_struct.signature));
      g_value_unset (&value);
    }
  return ret;
}

static gboolean
_interface_skeleton_handle_set_property (
  GDBusConnection *connection G_GNUC_UNUSED,
  const gchar *sender G_GNUC_UNUSED,
  const gchar *object_path G_GNUC_UNUSED,
  const gchar *interface_name G_GNUC_UNUSED,
  const gchar *property_name,
  GVariant *variant,
  GError **error,
  gpointer user_data)
{
  InterfaceSkeleton *skeleton = INTERFACE_SKELETON (user_data);
  GValue value = G_VALUE_INIT;
  GParamSpec *pspec;
  _ExtendedGDBusPropertyInfo *info;
  gboolean ret;
  ret = FALSE;
  info = (_ExtendedGDBusPropertyInfo *) g_dbus_interface_info_lookup_property ((GDBusInterfaceInfo *) &_interface_interface_info.parent_struct, property_name);
  g_assert (info != NULL);
  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (skeleton), info->hyphen_name);
  if (pspec == NULL)
    {
      g_set_error (error, G_DBUS_ERROR, G_DBUS_ERROR_INVALID_ARGS, "No property with name %s", property_name);
    }
  else
    {
      if (info->use_gvariant)
        g_value_set_variant (&value, variant);
      else
        g_dbus_gvariant_to_gvalue (variant, &value);
      g_object_set_property (G_OBJECT (skeleton), info->hyphen_name, &value);
      g_value_unset (&value);
      ret = TRUE;
    }
  return ret;
}

static const GDBusInterfaceVTable _interface_skeleton_vtable =
{
  _interface_skeleton_handle_method_call,
  _interface_skeleton_handle_get_property,
  _interface_skeleton_handle_set_property,
  {NULL}
};

static GDBusInterfaceInfo *
interface_skeleton_dbus_interface_get_info (GDBusInterfaceSkeleton *skeleton G_GNUC_UNUSED)
{
  return interface_interface_info ();
}

static GDBusInterfaceVTable *
interface_skeleton_dbus_interface_get_vtable (GDBusInterfaceSkeleton *skeleton G_GNUC_UNUSED)
{
  return (GDBusInterfaceVTable *) &_interface_skeleton_vtable;
}

static GVariant *
interface_skeleton_dbus_interface_get_properties (GDBusInterfaceSkeleton *_skeleton)
{
  InterfaceSkeleton *skeleton = INTERFACE_SKELETON (_skeleton);

  GVariantBuilder builder;
  guint n;
  g_variant_builder_init (&builder, G_VARIANT_TYPE ("a{sv}"));
  if (_interface_interface_info.parent_struct.properties == NULL)
    goto out;
  for (n = 0; _interface_interface_info.parent_struct.properties[n] != NULL; n++)
    {
      GDBusPropertyInfo *info = _interface_interface_info.parent_struct.properties[n];
      if (info->flags & G_DBUS_PROPERTY_INFO_FLAGS_READABLE)
        {
          GVariant *value;
          value = _interface_skeleton_handle_get_property (g_dbus_interface_skeleton_get_connection (G_DBUS_INTERFACE_SKELETON (skeleton)), NULL, g_dbus_interface_skeleton_get_object_path (G_DBUS_INTERFACE_SKELETON (skeleton)), "cn.lingmoos.interface", info->name, NULL, skeleton);
          if (value != NULL)
            {
              g_variant_take_ref (value);
              g_variant_builder_add (&builder, "{sv}", info->name, value);
              g_variant_unref (value);
            }
        }
    }
out:
  return g_variant_builder_end (&builder);
}

static void
interface_skeleton_dbus_interface_flush (GDBusInterfaceSkeleton *_skeleton)
{
}

static void interface_skeleton_iface_init (InterfaceIface *iface);
#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
G_DEFINE_TYPE_WITH_CODE (InterfaceSkeleton, interface_skeleton, G_TYPE_DBUS_INTERFACE_SKELETON,
                         G_ADD_PRIVATE (InterfaceSkeleton)
                         G_IMPLEMENT_INTERFACE (TYPE_INTERFACE, interface_skeleton_iface_init))

#else
G_DEFINE_TYPE_WITH_CODE (InterfaceSkeleton, interface_skeleton, G_TYPE_DBUS_INTERFACE_SKELETON,
                         G_IMPLEMENT_INTERFACE (TYPE_INTERFACE, interface_skeleton_iface_init))

#endif
static void
interface_skeleton_finalize (GObject *object)
{
  InterfaceSkeleton *skeleton = INTERFACE_SKELETON (object);
  g_list_free_full (skeleton->priv->changed_properties, (GDestroyNotify) _changed_property_free);
  if (skeleton->priv->changed_properties_idle_source != NULL)
    g_source_destroy (skeleton->priv->changed_properties_idle_source);
  g_main_context_unref (skeleton->priv->context);
  g_mutex_clear (&skeleton->priv->lock);
  G_OBJECT_CLASS (interface_skeleton_parent_class)->finalize (object);
}

static void
interface_skeleton_init (InterfaceSkeleton *skeleton)
{
#if GLIB_VERSION_MAX_ALLOWED >= GLIB_VERSION_2_38
  skeleton->priv = interface_skeleton_get_instance_private (skeleton);
#else
  skeleton->priv = G_TYPE_INSTANCE_GET_PRIVATE (skeleton, TYPE_INTERFACE_SKELETON, InterfaceSkeletonPrivate);
#endif

  g_mutex_init (&skeleton->priv->lock);
  skeleton->priv->context = g_main_context_ref_thread_default ();
}

static void
interface_skeleton_class_init (InterfaceSkeletonClass *klass)
{
  GObjectClass *gobject_class;
  GDBusInterfaceSkeletonClass *skeleton_class;

  gobject_class = G_OBJECT_CLASS (klass);
  gobject_class->finalize = interface_skeleton_finalize;

  skeleton_class = G_DBUS_INTERFACE_SKELETON_CLASS (klass);
  skeleton_class->get_info = interface_skeleton_dbus_interface_get_info;
  skeleton_class->get_properties = interface_skeleton_dbus_interface_get_properties;
  skeleton_class->flush = interface_skeleton_dbus_interface_flush;
  skeleton_class->get_vtable = interface_skeleton_dbus_interface_get_vtable;

#if GLIB_VERSION_MAX_ALLOWED < GLIB_VERSION_2_38
  g_type_class_add_private (klass, sizeof (InterfaceSkeletonPrivate));
#endif
}

static void
interface_skeleton_iface_init (InterfaceIface *iface)
{
}

/**
 * interface_skeleton_new:
 *
 * Creates a skeleton object for the D-Bus interface <link linkend="gdbus-interface-cn-lingmoos-interface.top_of_page">cn.lingmoos.interface</link>.
 *
 * Returns: (transfer full) (type InterfaceSkeleton): The skeleton object.
 */
Interface *
interface_skeleton_new (void)
{
  return INTERFACE (g_object_new (TYPE_INTERFACE_SKELETON, NULL));
}

